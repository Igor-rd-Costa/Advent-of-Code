#pragma once
#include <chrono>

namespace AoC {

	class Timer
	{
	public:
		Timer();
		~Timer() = default;

		long long GetTime();

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	};

}