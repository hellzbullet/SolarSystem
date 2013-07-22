#include "logger.h"

const QString Logger::LoggerDirectoryPath = "Log";
const QString Logger::LoggerFilePath = "log.log";
const QString Logger::LoggerPath = LoggerDirectoryPath + QDir::separator() + LoggerFilePath;

Logger::Logger()
{
	SetUpFiles();
}

void Logger::SetUpFiles()
{
	QDir dir(LoggerDirectoryPath);
	if (!dir.exists(LoggerDirectoryPath)) {
		dir.mkpath(LoggerDirectoryPath);
	}

	QFile file(LoggerPath);
	if (!file.exists(LoggerPath)) {
		if(!file.open(QFile::Text | QFile::ReadWrite)) {
			SystemDatabase::Instance()->insertLog("Cannot make a log file", Logger::TypeString(LogType::ERROR));
		}
	}
}

void Logger::Log(QString message, LogType type)
{
	QString strType;
	switch(type) {
		case LogType::ERROR:
			strType = "ERROR";
			break;
		case LogType::NORMAL:
			strType = "NORMAL";
			break;
		default:
			strType = "UNKNOWN";
	}

	QString strToAppend = QDateTime::currentDateTime().toString(Qt::ISODate);

	if (type == LogType::ERROR) strToAppend += " " + strType;
	strToAppend += " " + message + "\n";

	QFile file(LoggerPath);
	if (file.open(QFile::ReadWrite | QFile::Append)) {
		QTextStream s(&file);
		s << strToAppend;
	}

	SystemDatabase::Instance()->insertLog(message, Logger::TypeString(type));
}

Logger* Logger::Instance()
{
	if (logger == NULL) {
		logger = new Logger();
	}
	return logger;
}

QString Logger::TypeString(LogType type)
{
	QString strType;
	switch(type) {
		case LogType::ERROR:
			strType = "ERROR";
			break;
		case LogType::NORMAL:
			strType = "NORMAL";
			break;
		default:
			strType = "UNKNOWN";
	}
	return strType;
}

void Logger::Dispose()
{
	if (logger != NULL) {
		delete logger;
	}
}

Logger* Logger::logger = new Logger();


