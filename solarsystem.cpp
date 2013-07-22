#include "solarsystem.h"

SolarSystem::SolarSystem(QObject *parent) : QObject(parent)
{
	reader			= new PowerReader(this);
	service			= new WebService(this);
	mutex			= new QMutex();
	waitCondition	= new QWaitCondition();

	programRunning = true;

	connect(reader, SIGNAL(PowerChanged(qint32)), this, SLOT(PowerChanged(qint32)));

}

SolarSystem::~SolarSystem()
{
	delete mutex;
	delete waitCondition;

	dispose();
}

void SolarSystem::Run()
{
	Logger::Instance()->Log("Starting program!");

	qint32 cycle = 1;
	while(programRunning) {
		reader->ReadPower();
		mutex->lock ();
		waitCondition->wait(mutex, 10000);
	}

	Logger::Instance()->Log("Shutting down program!");

	dispose();
}

void SolarSystem::PowerChanged(qint32 newPower)
{
	PowerOutput::Output(newPower);
}

void SolarSystem::Stop() {
	programRunning = false;
	waitCondition->wakeAll();
}

void SolarSystem::dispose()
{
	Logger::Dispose();
	SystemDatabase::Dispose();
}
