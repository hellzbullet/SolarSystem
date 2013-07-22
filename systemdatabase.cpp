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
	QString query = QString("INSERT INTO power (PowerValue, UsedPowerValue, Date) VALUES (%1, %2, %3)").arg(power).arg(usedPower).arg(QDateTime::currentMSecsSinceEpoch());
	QSqlQuery sqlQuery;
	sqlQuery.exec(query);
}

void SystemDatabase::Init() {
	if (!db->isOpen()) return;

	QString query1 = "CREATE TABLE IF NOT EXISTS devices (Id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, DevicePower INTEGER NOT NULL, IsRunning INTEGER NOT NULL, IsUserControlled INTEGER NOT NULL, StartTime INTEGER NOT NULL, RunTime INTEGER NOT NULL, Pin INTEGER NOT NULL, Priority INTEGER NOT NULL)";
	QString query2 = "CREATE TABLE IF NOT EXISTS logs (Id INTEGER PRIMARY KEY AUTOINCREMENT, Message TEXT NOT NULL, Date INTEGER NOT NULL, Type TEXT NOT NULL)";
	QString query3 = "CREATE TABLE IF NOT EXISTS power (Id INTEGER PRIMARY KEY AUTOINCREMENT, Date INTEGER NOT NULL, PowerValue INTEGER NOT NULL, UsedPowerValue INTEGER NOT NULL)";

	executeQuery(query1);
	executeQuery(query2);
	executeQuery(query3);
}


QList<Device*>* SystemDatabase::getDevices()
{
	if (!db->isOpen()) return NULL;

	QList<Device*>* list = new QList<Device*>();

	QString query = "SELECT * FROM devices";
	QSqlQuery sqlQuery;

	if (sqlQuery.exec(query)) {
		auto record = sqlQuery.record();
		while (sqlQuery.next()) {
			Device* d = new Device();

			d->DevicePower == sqlQuery.value(record.indexOf("DevicePower"));
			d->Id == sqlQuery.value(record.indexOf("Id"));
			d->IsRunning == sqlQuery.value(record.indexOf("IsRunning"));
			d->IsUserControlled == sqlQuery.value(record.indexOf("IsUserControlled"));
			d->StartTime == sqlQuery.value(record.indexOf("StartTime"));
			d->RunTime == sqlQuery.value(record.indexOf("RunTime"));
			d->Pin == sqlQuery.value(record.indexOf("Pin"));
			d->Priority == sqlQuery.value(record.indexOf("Priority"));
			d->Name == sqlQuery.value(record.indexOf("Name"));

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
		QString query = QString("UPDATE devices SET IsRunning = %1, RunTime = %2, StartTime = %3 WHERE Id = %4").arg(device->IsRunning).arg(device->RunTime).arg(device->StartTime).arg(device->Id);
		executeQuery(query);
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

	QString query = QString("INSERT INTO logs (Message, Type, Date) VALUES ('%1', '%2', %3)").arg(message).arg(strType).arg(QDateTime::currentMSecsSinceEpoch());
	executeQuery(query);
}

void SystemDatabase::executeQuery(QString query) {
	QSqlQuery sqlQuery;
	sqlQuery.exec(query);
}

SystemDatabase* SystemDatabase::Instance()
{
	if (database == NULL) {
		database = new SystemDatabase();
	}
	return database;
}

void SystemDatabase::Dispose()
{
	if (database != NULL) {
		delete database;
	}
}

SystemDatabase* SystemDatabase::database = new SystemDatabase();
