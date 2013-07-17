#ifndef IPFINDER_H
#define IPFINDER_H

#include <QObject>
#include "QString"

class IPFinder : public QObject
{
		Q_OBJECT
	public:
		explicit IPFinder(QObject *parent = 0);

		void findIP();
		
	signals:
		void IPFound(QString newIP);
		void finished();

	public slots:
		
};

#endif // IPFINDER_H
