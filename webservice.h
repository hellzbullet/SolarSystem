#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <QObject>
#include "QLocalServer"
#include "QNetworkAccessManager"
#include "QUdpSocket"
#include "QHostAddress"
#include "QByteArray"
#include "QDebug"

class WebService : public QObject
{
		Q_OBJECT
	public:
		explicit WebService(QObject *parent = 0);
		~WebService();
		
	private:
		QUdpSocket* socket;

	signals:
		
	public slots:
		void readDatagram();
};

#endif // WEBSERVICE_H
