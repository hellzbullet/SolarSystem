#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <QObject>
#include "systemdatabase.h"
#include "iostream"
#include "QThread"
#include "logger.h"
#include "powerreader.h"
#include "poweroutput.h"

class SolarSystem : public QObject
{
		Q_OBJECT
	public:
		explicit SolarSystem(QObject *parent = 0);
		~SolarSystem();

		void Run();

	private:
		SystemDatabase* db;
		PowerReader*	reader;

		bool programRunning;

	signals:
		
	public slots:
		void PowerChanged(qint32 newPower);
};

#endif // SOLARSYSTEM_H
