#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{
	SetUpFiles();
}

void Logger::SetUpFiles()
{
	if (!QDir::exists(LoggerDirectoryPath)) {
		QDir::mkPath(LoggerDirectoryPath);
	}

	if (!QFile::exists(LoggerPath)) {
		if(!QFile::open(QFile::Text | QFile::ReadWrite)) {

		}
	}
}

void Logger::Log(QString message, LogType type)
{
	QString strType;
	switch(type) {
		case ERROR:
			strType = "ERROR";
			break;
		case NORMAL:
			strType = "NORMAL";
			break;
		default:
			strType = "UNKNOWN";
	}

	QString strToAppend = QString::number(QDateTime::currentMSecsSinceEpoch());

	if (type == LogType.ERROR) strToAppend += " " + strType;
	strToAppend += " " + message + "\n";

	QFile file(LoggerPath);
	if (file.open(QFile::ReadWrite)) {
		QTextStream s(&file, QFile::ReadWrite | QFile::Append);
		s << strToAppend;
	}
	// TODO ADD TO DATABASE
}

Logger* Logger::Instance()
{
	if (logger == null) {
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


