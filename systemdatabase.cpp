#include "systemdatabase.h"

using namespace std;

SystemDatabase::SystemDatabase(QObject *parent) : QObject(parent)
{
	db = &QSqlDatabase::addDatabase("MySQL");
	db->setDatabaseName("SolarSystem");
	db->setHostName("localhost");
	db->setPassword("CrimeruleZ12345");
	db->setUserName("SolarSystem");
	if (!db->open()) {
		cerr << "Could not open database!" << endl;
	} else {
		cout << "Database opened: " << db->isOpen() << endl;
	}

	QStringList drivers = QSqlDatabase::drivers();

	for (int i = 0; i < drivers.length(); i++) {
		cout << drivers[i].toUtf8().constData() << endl;
	}

	Init();
}

SystemDatabase::~SystemDatabase()
{
	delete db;
}

void SystemDatabase::Init() {
	if (!db->isOpen()) return;

	auto tables = db->tables();
	cout << "Length: " << tables.length() << endl;
}
