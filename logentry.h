#ifndef LOGENTRY_H
#define LOGENTRY_H

#include "QtGlobal"
#include "QString"
#include "QDateTime"

class LogEntry
{
	public:
		qint32 Id;
		qint64 Date;
		QString Message;
		QString Type;
};

#endif // LOGENTRY_H
