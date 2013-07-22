#include "ipfinder.h"

IPFinder::IPFinder(QObject *parent) : QObject(parent)
{
}

void IPFinder::findIP()
{
	emit(IPFound("192.168.1.168"));
}
