#ifndef LOGGER_H
#define LOGGER_H

#include "QObject"
#include "QString"
#include "QFile"
#include "QDateTime"
#include "QDir"
#include "QTextStream"

enum class LogType {
	NORMAL,
	ERROR
};

class Logger : public QObject
{
		Q_OBJECT
	public:
		static Logger* Instance();
		static void Dispose();

		static const QString LoggerDirectoryPath = "Log/";
		static const QString LoggerFilePath = "log";
		static const QString LoggerPath = LoggerDirectoryPath + LoggerFilePath;

		void Log(QString message, LogType type = LogType::NORMAL);

	private:
		explicit Logger(QObject *parent = 0);

		static Logger* logger;

	signals:

	public slots:

};

#endif // LOGGER_H
