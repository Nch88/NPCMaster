#pragma once
using namespace std::chrono;
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

