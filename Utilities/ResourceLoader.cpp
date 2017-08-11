#include "ResourceLoader.h"


ResourceLoader::ResourceLoader()
{
}


ResourceLoader::~ResourceLoader()
{
}

Resource* ResourceLoader::loadResource(const std::string& path)
{
	std::fstream input(path.c_str(),std::iostream::ate);
	UINT size=input.tellg();
	input.seekg(0);
	char* data=new char[size];
	input.read(data,size);
	Resource* resource=new Resource(size,data);
	input.close();
	return resource;
}
