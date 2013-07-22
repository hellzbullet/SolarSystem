#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <QObject>
#include "systemdatabase.h"
#include "iostream"
#include "QDebug"
#include "QThread"
#include "logger.h"
#include "powerreader.h"
#include "poweroutput.h"
#include "webservice.h"
#include "signal.h"
#include "QMutex"
#include "QWaitCondition"

class SolarSystem : public QObject
{
		Q_OBJECT
	public:
		explicit SolarSystem(QObject *parent = 0);
		~SolarSystem();

		void Run();
		void Stop();

	private:
		SystemDatabase* db;
		PowerReader*	reader;
		WebService*		service;
		QMutex*			mutex;
		QWaitCondition* waitCondition;

		bool programRunning;

		void dispose();

	signals:
		
	public slots:
		void PowerChanged(qint32 newPower);
};

#endif // SOLARSYSTEM_H
