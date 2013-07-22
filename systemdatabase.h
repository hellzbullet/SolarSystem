#ifndef SYSTEMDATABASE_H
#define SYSTEMDATABASE_H

#include <QObject>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlDriver"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlResult"
#include "QtSql/QSqlTableModel"
#include "QtSql/QSqlRecord"
#include "QDateTime"
#include "QStringList"
#include "iostream"
#include "QDebug"
#include "device.h"
#include "logger.h"
#include "QDir"

class SystemDatabase : public QObject
{
		Q_OBJECT
	public:
		explicit SystemDatabase(QObject *parent = 0);
		~SystemDatabase();

		void insertPower(qint32 power, qint32 usedPower);
		void insertLog(QString message, LogType type = LogType::NORMAL);
		void updateDevices(QList<Device*>* devices);

		QList<Device*>* getDevices();

	private:
		void Init();

		QSqlDatabase* db;

	signals:
		
	public slots:
		
};

#endif // SYSTEMDATABASE_H
