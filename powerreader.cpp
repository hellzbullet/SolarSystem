#include "powerreader.h"

PowerReader::PowerReader(QObject *parent) : QObject(parent)
{
	logger =  new Logger(this);
	ipFinder = new IPFinder(this);

	connect(ipFinder, SIGNAL(IPFound(QString), this, SLOT(IPFound(QString));
}

void PowerReader::ReadPower()
{
}


void PowerReader::IPFound(QString IP)
{
	currentIP = "http://" + IP + "/home.htm";
}
