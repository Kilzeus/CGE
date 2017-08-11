#pragma once
#include "Counter.h"
#include<Windows.h>
class WindowsCounter :
	public Counter
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	double timeDelta;
public:
	WindowsCounter();
	double getTimeDelta();
	void start();
	void end();
};

