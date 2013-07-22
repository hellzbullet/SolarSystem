#include "poweroutput.h"

void PowerOutput::Output(qint32 power)
{
	QList<Device*>* optimalDevices = getOptimalDevices(SystemDatabase::Instance()->getDevices(), power);

	SystemDatabase::Instance()->insertPower(power, powerSum(optimalDevices));
}

QList<Device*>* PowerOutput::getOptimalDevices(QList<Device*>* devices, qint32 power)
{
	QHash<qint32, QList<Device*>*> priorityList;
	qint32 remainingPower = power;

	for (int i = 0; i < devices->length(); i++) {
		Device* d = devices->at(i);
		if (d->IsUserControlled && d->IsRunning) remainingPower -= d->DevicePower;
		else if (!d->IsUserControlled) {
			if (!priorityList.contains(d->Priority)) {
				priorityList.insert(d->Priority, new QList<Device*>());
			}
			priorityList[d->Priority]->append(d);
		}
	}

	QList<Device*>* optimalDevices = new QList<Device*>();
	QList<qint32> keys = priorityList.keys();

	qSort(keys);

	for (int i = keys.length() - 1; i >= 0; i--) {
		QList<Device*>* optimalForPriority = getOptimalDevicesForPriority(priorityList[keys[i]], remainingPower);

		for (int i = 0; i < optimalForPriority->length(); i++) {
			remainingPower -= optimalForPriority->at(i)->DevicePower;
		}

		optimalDevices->append(*optimalForPriority);
	}
	return optimalDevices;
}

QList<Device*>* PowerOutput::getOptimalDevicesForPriority(QList<Device*>* devices, qint32 remainingPower)
{
	QList<Device*>* optimalDevices = new QList<Device*>();
	getOptimalDevices(devices, remainingPower, optimalDevices, NULL, 0);
	return optimalDevices;
}

void PowerOutput::getOptimalDevices(QList<Device*>* devices, qint32 remainingPower, QList<Device*>* optimalDevices, QList<Device*>* currentSolution, qint32 index)
{
	if (currentSolution == NULL) {
		currentSolution = new QList<Device*>();
	}

	QList<Device*>* solution = new QList<Device*>(*currentSolution);

	if (index >= devices->length()) {
		if (powerSum(solution) > powerSum(optimalDevices)) {
			optimalDevices->clear();
			optimalDevices->append(*solution);
		}
		return;
	}

	qint32 powerRemaining = remainingPower;

	for (int i = 0; i < devices->length(); i++) {
		if (devices->at(i)->DevicePower <= powerRemaining && !solution->contains(devices->at(i))) {
			solution->append(devices->at(i));
			powerRemaining -= devices->at(i)->DevicePower;
		}
		getOptimalDevices(devices, powerRemaining, optimalDevices, solution, index + 1);
	}
}

qint32 PowerOutput::powerSum(const QList<Device*>* devices) {
	qint32 sum = 0;
	for (int i = 0; i < devices->length(); i++) {
		sum += devices->at(i)->DevicePower;
	}
	return sum;
}
