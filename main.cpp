#include <QCoreApplication>
#include "solarsystem.h"
#include "logger.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	SolarSystem* s = new SolarSystem();
	s->Run();

	delete s;

	Logger::Dispose();

	return a.exec();
}
