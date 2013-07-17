#ifndef POWER_H
#define POWER_H

#include "QtGlobal"
#include "QString"
#include "QDateTime"

class Power
{
	public:
		qint32 Id;
		qint64 Date;
		qint32 PowerValue;
		qint32 UsedPowerValue;
};

#endif // POWER_H
