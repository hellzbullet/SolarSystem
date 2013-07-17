#ifndef IPFINDER_H
#define IPFINDER_H

#include <QObject>
#include "QString"

class IPFinder : public QObject
{
		Q_OBJECT
	public:
		explicit IPFinder(QObject *parent = 0);
		
	signals:
		void IPFound(QString newIP);
	public slots:
		
};

#endif // IPFINDER_H
