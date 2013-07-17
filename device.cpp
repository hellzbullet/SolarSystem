#include "device.h"

void Device::Start()
{
	if (IsRunning == true) return;

	IsRunning = true;
	StartTime = QDateTime::currentMSecsSinceEpoch();
}

void Device::Stop()
{
	if (IsRunning == false) return;

	IsRunning = false;
	RunTime += QDateTime::currentMSecsSinceEpoch() - StartTime;
	StartTime = -1;
}
