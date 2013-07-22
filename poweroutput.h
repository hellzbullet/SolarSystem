#ifndef POWEROUTPUT_H
#define POWEROUTPUT_H

#include "QtGlobal"
#include "iostream"
#include "QList"
#include "device.h"
#include "QDebug"

class PowerOutput
{
	public:
		static void Output(qint32 power);

	private:
		static QList<Device*>* getOptimalDevices(QList<Device*>* devices, qint32 power);
		static QList<Device*>* getOptimalDevicesForPriority(QList<Device*>* devices, qint32 remainingPower);
		static void getOptimalDevices(QList<Device*>* devices, qint32 remainingPower, QList<Device*>* optimalDevices, QList<Device*>* currentSolution, qint32 index);
		static qint32 powerSum(const QList<Device*>* devices);
};

#endif // POWEROUTPUT_H
