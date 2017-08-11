#pragma once
class Counter
{
public:
	virtual double getTimeDelta() = 0;
	virtual void start() = 0;
	virtual void end() = 0;
};

