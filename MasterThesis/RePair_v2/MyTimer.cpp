#include "stdafx.h"
#include "MyTimer.h"


MyTimer::MyTimer()
{
}


MyTimer::~MyTimer()
{
}

void MyTimer::start()
{
	tStart = duration_cast< milliseconds >(
		high_resolution_clock::now().time_since_epoch()
		);
}

void MyTimer::stop()
{
	tStop = duration_cast< milliseconds >(
		high_resolution_clock::now().time_since_epoch()
		);
}

long long MyTimer::getTime()
{
	milliseconds result = tStop - tStart;
	tStart = (milliseconds)0;
	tStop = (milliseconds)0;
	return result.count();
}