#include "powerreader.h"

using namespace std;

PowerReader::PowerReader(QObject *parent) : QObject(parent)
{
	logger = Logger::Instance();
	ipFinder = new IPFinder(this);
	networkManager = new QNetworkAccessManager(this);

	currentIP = "http://192.168.1.168/home.htm";

	connect(ipFinder, SIGNAL(IPFound(QString)), this, SLOT(IPFound(QString)));
	connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}

void PowerReader::ReadPower()
{
	if (currentIP == "") {
		ipFinder->findIP();

		QEventLoop loop;
		connect(ipFinder, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();

		if (currentIP == "") return;
	}

	auto reply = networkManager->get(QNetworkRequest(QUrl(currentIP)));

	QEventLoop loop;
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();
}

void PowerReader::IPFound(QString IP)
{
	currentIP = "http://" + IP + "/home.htm";
}

void PowerReader::downloadFinished(QNetworkReply* reply)
{
	QIODevice* content = static_cast<QIODevice*>(reply);
	while (content->canReadLine()) {
		QString line = QString(content->readLine()).trimmed();
		if (line.toLower().contains(QRegExp("id=\"power\""))) {
			QString power = normalize(line.toLower());

			bool isKW = power.contains("kw");
			double powerValue = power.remove(QRegExp(" .*")).toDouble();
			if (isKW) powerValue *= 1000;

			emit(PowerChanged((qint32)powerValue));
			break;
		}
	}
	content->deleteLater();
}

QString PowerReader::normalize(const QString str)
{
	QString newStr = "";
	QByteArray array = str.toUtf8();

	bool remove = false;
	for (int i = 0; i < array.length(); i++) {
		if (array[i] == '<') {
			remove = true;
			continue;
		}

		if (array[i] == '>') {
			remove = false;
			continue;
		}

		if (remove) continue;

		newStr += array[i];
	}

	return newStr;
}
