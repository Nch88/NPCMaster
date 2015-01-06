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
	time(&tStart);
}

void MyTimer::stop()
{
	time(&tStop);
}

float MyTimer::getTime()
{
	return tStop - tStart;
}