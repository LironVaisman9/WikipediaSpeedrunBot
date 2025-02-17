#pragma once

#include <chrono>

class Timer
{
public:
	Timer();
	
public:
	void start();
	void stop();

	/// <summary>
	/// Template function that stops the timer,
	/// and tells the exact time in <DURATION_TYPE>
	/// 
	/// Duration Type can be std::chorno::seconds, std::chorno::milliseconds, etc..
	/// </summary>
	/// <typeparam name="Duration">Chrono duration type | microseconds if not specified</typeparam>
	/// <returns>Amount of <Chrono Duration></returns>
	template <typename Duration = std::chrono::milliseconds>
	size_t getDuration()
	{
		stop();
		return std::chrono::duration_cast<Duration>(_endTime - _beginTime).count();
	}

private:
	std::chrono::high_resolution_clock::time_point _beginTime;
	std::chrono::high_resolution_clock::time_point _endTime;
};

