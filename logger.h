#ifndef LOGGER_H
#define LOGGER_H

#include "QString"
#include "QFile"
#include "QDateTime"
#include "QDir"
#include "QTextStream"
#include "systemdatabase.h"

enum class LogType {
	NORMAL,
	ERROR
};

class Logger
{
	public:
		Logger();

		static Logger* Instance();
		static QString TypeString(LogType type);

		static void Dispose();

		void SetUpFiles();
		void Log(QString message, LogType type = LogType::NORMAL);

		static const QString LoggerDirectoryPath;
		static const QString LoggerFilePath;
		static const QString LoggerPath;

	private:
		static Logger* logger;
};

#endif // LOGGER_H
