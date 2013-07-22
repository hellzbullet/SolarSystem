#ifndef SOLARSYSTEMUTILS_H
#define SOLARSYSTEMUTILS_H

#include <QObject>
#include "QEventLoop"

class SolarSystemUtils : public QObject
{
		Q_OBJECT
	public:
		static void waitForAsync(const QObject* sender, const char* signal);

	signals:
		
	public slots:
		
};

#endif // SOLARSYSTEMUTILS_H
