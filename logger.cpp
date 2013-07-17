#include "logger.h"

const QString Logger::LoggerDirectoryPath = "Log/";
const QString Logger::LoggerFilePath = "log";
const QString Logger::LoggerPath = LoggerDirectoryPath + LoggerFilePath;

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
			// TODO LOG TO DATABASE
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

	QString strToAppend = QString::number(QDateTime::currentMSecsSinceEpoch());

	if (type == LogType::ERROR) strToAppend += " " + strType;
	strToAppend += " " + message + "\n";

	QFile file(LoggerPath);
	if (file.open(QFile::ReadWrite | QFile::Append | QFile::Text)) {
		QTextStream s(&file);
		s << strToAppend;
	}
	// TODO ADD TO DATABASE
}

Logger* Logger::Instance()
{
	if (logger == NULL) {
		logger = new Logger();
	}
	return logger;
}

void Logger::Dispose()
{
	if (logger != NULL) {
		delete logger;
	}
}

Logger* Logger::logger = new Logger();


