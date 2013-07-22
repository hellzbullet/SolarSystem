#include "solarsystemutils.h"

void SolarSystemUtils::waitForAsync(const QObject* sender, const char* signal)
{
	QEventLoop loop;
	connect(sender, signal, &loop, SLOT(quit()));
	loop.exec();
}




