#pragma once
#include"Definitions.h"
class Resource
{
	UINT size;
	UINT pitch;
	void* data;
public:
	Resource();
	Resource(UINT size,void* data);
	Resource(UINT size,UINT pitch,void* data);
	~Resource();
	void set(UINT size,void* data);
	UINT getSize();
	void* getData();
	void setPitch(UINT pitch);
	UINT getPitch() const;
};

