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
	tStart = boost::chrono::high_resolution_clock::now();
	tStop = boost::chrono::high_resolution_clock::now();
}

void MyTimer::stop()
{
	tStop = boost::chrono::high_resolution_clock::now();
}

boost::chrono::milliseconds MyTimer::getTime()
{
	boost::chrono::milliseconds result =
		boost::chrono::duration_cast<boost::chrono::milliseconds>
		(this->tStop - this->tStart);
	return result;
}

boost::chrono::microseconds MyTimer::getTimeMicro()
{
	boost::chrono::microseconds result =
		boost::chrono::duration_cast<boost::chrono::microseconds>
		(this->tStop - this->tStart);
	return result;
}

boost::chrono::nanoseconds MyTimer::getTimeNano()
{
	boost::chrono::nanoseconds result =
		boost::chrono::duration_cast<boost::chrono::nanoseconds>
		(this->tStop - this->tStart);
	return result;
}