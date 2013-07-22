#include <QCoreApplication>
#include "solarsystem.h"
#include "logger.h"
#include "webservice.h"
#include "signal.h"
#include "QDebug"

void signalHandler(int signum)
{
	qDebug() << "Caught " << signum;
}

void setUpHandlers() {
	//signal(SIGTERM, signalHandler);
	//signal(SIGABRT, signalHandler);
	//signal(SIGABRT_COMPAT, signalHandler);
	//signal(SIGBREAK, signalHandler);
	//signal(SIGFPE, signalHandler);
	//signal(SIGILL, signalHandler);
	//signal(SIGINT, signalHandler);
	//signal(SIGSEGV, signalHandler);
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//setUpHandlers ();

	SolarSystem* s = new SolarSystem();
	s->Run();

	return a.exec();
}
