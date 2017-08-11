#pragma once
#include<fstream>
#include"Resource.h"
class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();
	Resource* loadResource(const std::string& path);
};

