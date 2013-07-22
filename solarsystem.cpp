#include "solarsystem.h"

using namespace std;

SolarSystem::SolarSystem(QObject *parent) : QObject(parent)
{
	db				= new SystemDatabase(this);
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
}

void SolarSystem::Run()
{
	Logger::Instance()->Log("Starting program!");

	while(programRunning) {
		reader->ReadPower();
		mutex->lock ();
		waitCondition->wait(mutex, 10000);
	}

	Logger::Instance()->Log("Shutting down program!");
}

void SolarSystem::PowerChanged(qint32 newPower)
{
	qDebug() << newPower;
	PowerOutput::Output(newPower);
}

void SolarSystem::Stop() {
	programRunning = false;
	waitCondition->wakeAll();
}
