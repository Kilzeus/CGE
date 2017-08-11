#include "Resource.h"


Resource::Resource()
:size(0),data(0)
{
}


Resource::Resource(UINT size,void* data)
:size(size),data(data)
{
}


Resource::Resource(UINT size,UINT pitch,void* data)
	:size(size),pitch(pitch),data(data)
{
}


Resource::~Resource(void)
{
	//if(data) delete[] data;
}

void Resource::set(UINT size,void* data)
{
	//if (this->data) delete[] this->data;
	this->size=size;
	this->data=data;
}

UINT Resource::getSize()
{
	return size;
}

void* Resource::getData()
{
	return data;
}


void Resource::setPitch(UINT pitch)
{
	this->pitch = pitch;
}


UINT Resource::getPitch() const
{
	return pitch;
}