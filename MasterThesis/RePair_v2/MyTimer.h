#pragma once
using namespace std::chrono;
class MyTimer
{
	boost::chrono::high_resolution_clock::time_point tStart;
	boost::chrono::high_resolution_clock::time_point tStop;
public:
	MyTimer();
	~MyTimer();

	void start();
	void stop();
	boost::chrono::milliseconds getTime();
	boost::chrono::microseconds getTimeMicro();
	boost::chrono::nanoseconds getTimeNano();
};