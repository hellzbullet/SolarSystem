#ifndef DEVICE_H
#define DEVICE_H

#include "QtGlobal"
#include "QString"
#include "QDateTime"

class Device
{
	public:
		Device();

		qint32 Id;
		QString Name;
		qint32 DevicePower;
		qint32 Pin;
		qint64 StartTime;
		bool IsRunning;
		bool IsUserControlled;
		qint32 Priority;
		qint64 RunTime;

		void Start();
		void Stop();
};

#endif // DEVICE_H
