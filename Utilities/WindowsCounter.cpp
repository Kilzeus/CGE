#include "WindowsCounter.h"
#include<Windows.h>


WindowsCounter::WindowsCounter()
	:timeDelta(0.)
{
	QueryPerformanceFrequency(&frequency);
}


double WindowsCounter::getTimeDelta()
{
	return timeDelta;
}


void WindowsCounter::start()
{
	QueryPerformanceCounter(&startTime);
}


void WindowsCounter::end()
{
	QueryPerformanceCounter(&endTime);
	LONGLONG interval = endTime.QuadPart - startTime.QuadPart;
	timeDelta = (double)interval / (double)frequency.QuadPart;
}
