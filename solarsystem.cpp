#include "solarsystem.h"

using namespace std;

SolarSystem::SolarSystem(QObject *parent) : QObject(parent)
{
	db = new SystemDatabase(this);
	reader = new PowerReader(this);

	programRunning = true;

	connect(reader, SIGNAL(PowerChanged(qint32)), this, SLOT(PowerChanged(qint32)));
}

SolarSystem::~SolarSystem()
{
}

void SolarSystem::Run()
{
	Logger::Instance()->Log("Starting program!");

	while(programRunning) {
		reader->ReadPower();
		QThread::sleep(10);
	}

	Logger::Instance()->Log("Shutting down program!");
}

void SolarSystem::PowerChanged(qint32 newPower)
{
	PowerOutput::Output(newPower);
}
