#include "device.h"

Device::Device()
{
	IsRunning = false;
	StartTime = -1;
	IsUserControlled = false;
	RunTime = 0;
}

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
