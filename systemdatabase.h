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
#include "QDir"

class SystemDatabase : public QObject
{
		Q_OBJECT
	public:
		explicit SystemDatabase(QObject *parent = 0);
		~SystemDatabase();

		void insertPower(qint32 power, qint32 usedPower);
		void insertLog(QString message, QString type);
		void updateDevices(QList<Device*>* devices);

		QList<Device*>* getDevices();

		static SystemDatabase* Instance();
		static void Dispose();

	private:
		void Init();
		void executeQuery(QString query);

		QSqlDatabase db;

		static SystemDatabase* database;

	signals:
		
	public slots:
		
};

#endif // SYSTEMDATABASE_H
