#ifndef POWERREADER_H
#define POWERREADER_H

#include <QObject>
#include "QString"
#include "logger.h"
#include "ipfinder.h"


class PowerReader : public QObject
{
		Q_OBJECT
	public:
		explicit PowerReader(QObject *parent = 0);
		
		void ReadPower();

	private:
		QString currentIP;

		Logger* logger;
		IPFinder* ipFinder;

	signals:
		void PowerChanged(qint32 newPower);
		void ReadingCancelled();

	public slots:
		void IPFound(QString IP);
		
};

#endif // POWERREADER_H
