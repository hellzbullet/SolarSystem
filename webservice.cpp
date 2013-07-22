#include "webservice.h"

WebService::WebService(QObject *parent) : QObject(parent)
{
	socket = new QUdpSocket(this);
	socket->bind(QHostAddress::Any, 82);
	connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagram()));
}

WebService::~WebService()
{
	if (socket != NULL) {
		socket->close();
		delete socket;
	}
}

void WebService::readDatagram()
{
	while (socket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(socket->pendingDatagramSize());

		socket->readDatagram(datagram.data(), datagram.size());

		socket->userData (5);
		qDebug() << QString(datagram);
	}
}
