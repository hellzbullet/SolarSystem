#include "systemdatabase.h"

using namespace std;

SystemDatabase::SystemDatabase(QObject *parent) : QObject(parent)
{
	db = &QSqlDatabase::addDatabase("QSQLITE");

	#ifdef Q_OS_LINUX    // NOTE: We have to store database file into user home folder in Linux
		QString path(QDir::home().path());
		path.append(QDir::separator()).append("solarsystem.db.sqlite");
		path = QDir::toNativeSeparators(path);
		db->setDatabaseName(path);
	#else    // NOTE: File exists in the application private folder, in Symbian Qt implementation
		db->setDatabaseName("solarsystem.db.sqlite");
	#endif

	if (!db->open()) {
		qDebug() << "Could not open database!";
		qDebug() << db->lastError();
	} else {
		qDebug() << "Database opened: " << db->isOpen();
	}

	Init();
}

SystemDatabase::~SystemDatabase()
{
	delete db;
}

void SystemDatabase::insertPower(qint32 power, qint32 usedPower)
{
}

void SystemDatabase::Init() {
	if (!db->isOpen()) return;

	QSqlQuery sqlQuery(*db);
	if (!sqlQuery.exec("DROP TABLE devices")) {
		qDebug() << "Couldn't drop table devices";
	}
	if (!sqlQuery.exec("DROP TABLE logs")) {
		qDebug() << "Couldn't drop table logs";
	}
	if (!sqlQuery.exec("DROP TABLE power")) {
		qDebug() << "Couldn't drop table power";
	}

	QString query1 = "CREATE TABLE IF NOT EXISTS devices (Id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, DevicePower INTEGER NOT NULL, IsRunning INTEGER NOT NULL, IsUserControlled INTEGER NOT NULL, StartTime INTEGER NOT NULL, RunTime INTEGER NOT NULL, Pin INTEGER NOT NULL, Priority INTEGER NOT NULL)";
	QString query2 = "CREATE TABLE IF NOT EXISTS logs (Id INTEGER PRIMARY KEY AUTOINCREMENT, Message TEXT NOT NULL, Date INTEGER NOT NULL, Type TEXT NOT NULL)";
	QString query3 = "CREATE TABLE IF NOT EXISTS power (Id INTEGER PRIMARY KEY AUTOINCREMENT, Date INTEGER NOT NULL, PowerValue INTEGER NOT NULL, UsedPowerValue INTEGER NOT NULL)";

	if (!sqlQuery.exec(query1)) {
		qDebug() << "Couldn't create table devices";
	}
	if (!sqlQuery.exec(query2)) {
		qDebug() << "Couldn't create table logs";
	}
	if (!sqlQuery.exec(query3)) {
		qDebug() << "Couldn't create table power";
	}

	qDebug() << sqlQuery.lastError();

	auto tables = db->tables();
	qDebug() << "Length: " << tables.length() << endl;
}


QList<Device*>* SystemDatabase::getDevices()
{
	if (!db->isOpen()) return NULL;

	QList<Device*>* list = new QList<Device*>();

	QString query = "SELECT id, devicePower, isRunning, isUserControlled, startTime, name, pin, priority, runTime FROM devices";
	QSqlQuery sqlQuery;

	if (sqlQuery.exec(query)) {
		auto record = sqlQuery.record();
		while (sqlQuery.next()) {
			Device* d = new Device();

			d->DevicePower == sqlQuery.value(record.indexOf("devicePower"));
			d->Id == sqlQuery.value(record.indexOf("id"));
			d->IsRunning == sqlQuery.value(record.indexOf("isRunning"));
			d->IsUserControlled == sqlQuery.value(record.indexOf("isUserControlled"));
			d->StartTime == sqlQuery.value(record.indexOf("startTime"));
			d->RunTime == sqlQuery.value(record.indexOf("runTime"));
			d->Pin == sqlQuery.value(record.indexOf("pin"));
			d->Priority == sqlQuery.value(record.indexOf("priority"));
			d->Name == sqlQuery.value(record.indexOf("name"));

			list->append(d);
		}
	}

	return list;
}


void SystemDatabase::updateDevices(QList<Device*>* devices)
{
	if (!db->isOpen()) return;

	for (int i = 0; i < devices->length(); ++i) {
		Device* device = devices->at(i);
		QString query = QString("UPDATE devices SET isRunning = %1, runTime = %2, startTime = %3 WHERE id = %4").arg(QString(device->IsRunning), QString::number(device->RunTime), QString::number(device->StartTime), QString::number(device->Id));
		QSqlQuery sqlQuery;
		sqlQuery.exec(query);
	}
}


void SystemDatabase::insertLog(QString message, LogType type)
{
	if (!db->isOpen()) return;

	QString strType;
	switch (type) {
		case LogType::ERROR:
			strType = "ERROR";
			break;
		case LogType::NORMAL:
			strType = "NORMAL";
			break;
		default:
			strType = "UNKNOWN";
			break;
	}

	QString query = QString("INSERT INTO logs (message, type, date) VALUES (%1, %2, %3)").arg(message, strType, QString::number(QDateTime::currentMSecsSinceEpoch()));
	QSqlQuery sqlQuery;
	sqlQuery.exec(query);
}
