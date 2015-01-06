#include "stdafx.h"

#pragma once

class MyTimer
{
	time_t tStart;
	time_t tStop;
public:
	MyTimer();
	~MyTimer();

	void start();
	void stop();
	float getTime();
};

