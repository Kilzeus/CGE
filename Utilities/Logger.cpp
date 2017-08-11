#include"Logger.h"

Logger::Logger(std::string filename)
{
	if(filestream.is_open()) filestream.close();
	filestream.open(filename.c_str(),std::ios::out|std::ios::trunc);
}


void Logger::logEntry(std::string type,std::string description)
{
	if( filestream.is_open())
	{
		filestream << type.c_str() << ": ";
		filestream << description.c_str() << "\n";
		filestream.flush();
	}
}


void Logger::close()
{
	filestream.close();
}