#include "Timer.h"
#include <iostream>

namespace AoC {

	Timer::Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	long long Timer::GetTime()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();

		m_StartTimepoint = std::chrono::high_resolution_clock::now();

		return end - start;
	}
}