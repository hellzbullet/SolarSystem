#ifndef SYSTEMDATABASE_H
#define SYSTEMDATABASE_H

#include <QObject>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlDriver"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlResult"
#include "QtSql/QSqlTableModel"
#include "QStringList"
#include "iostream"

class SystemDatabase : public QObject
{
		Q_OBJECT
	public:
		explicit SystemDatabase(QObject *parent = 0);
		~SystemDatabase();

	private:
		void Init();

		QSqlDatabase* db;

	signals:
		
	public slots:
		
};

#endif // SYSTEMDATABASE_H
