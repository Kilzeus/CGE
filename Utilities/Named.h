#ifndef NAMED_HH
#define NAMED_HH

#include<string>

class Named
{

	public:
	
	const std::string& getName();
	
	protected:
	
	std::string name;
	
};

#endif