#include "stdafx.h"
using namespace std::chrono;
#pragma once

class MyTimer
{
	milliseconds tStart;
	milliseconds tStop;
public:
	MyTimer();
	~MyTimer();

	void start();
	void stop();
	long long getTime();
};

