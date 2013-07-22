#ifndef POWERREADER_H
#define POWERREADER_H

#include <QObject>
#include "QString"
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include "QtNetwork/QNetworkRequest"
#include "QIODevice"
#include "QEventLoop"
#include "QUrl"
#include "QRegExp"
#include "QRegularExpression"
#include "logger.h"
#include "ipfinder.h"
#include "iostream"
#include "QDebug"
#include "solarsystemutils.h"

class PowerReader : public QObject
{
		Q_OBJECT
	public:
		explicit PowerReader(QObject *parent = 0);
		
		void ReadPower();

	private:
		QString currentIP;
		QNetworkAccessManager* networkManager;

		Logger* logger;
		IPFinder* ipFinder;

		QString normalize(const QString str);

	signals:
		void PowerChanged(qint32 newPower);

	public slots:
		void IPFound(QString IP);
		void downloadFinished(QNetworkReply* reply);
};

#endif // POWERREADER_H
