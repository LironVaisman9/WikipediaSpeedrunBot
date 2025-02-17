#include "Timer.h"

Timer::Timer()
{}

void Timer::start()
{
	_beginTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
	_endTime = std::chrono::high_resolution_clock::now();
}