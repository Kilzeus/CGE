#ifndef MYLOGGER_HH
#define MYLOGGER_HH

#include"Singleton.h"
#include<fstream>

class Logger
{
	std::fstream filestream;
public:
	Logger(std::string filename = "log.txt" );
	void logEntry( std::string type, std::string description );
	void close();
};

#endif