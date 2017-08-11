#ifndef BASEEXCEPTION_HH
#define BASEEXCEPTION_HH

#include<string>

class BaseException
{

	std::string description;
	std::string type;

	public:
	
	BaseException( std::string type, std::string description )
	{
		this->type = type;
		this->description = description;
	}
	const std::string& getDescription()
	{
		return this->description;
	};
	const std::string& getType()
	{
		return this->type;
	};
	
};

#endif