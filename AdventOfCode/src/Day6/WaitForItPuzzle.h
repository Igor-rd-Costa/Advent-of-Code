#pragma once
#include "Puzzle.h"

namespace AoC2023 {

	struct RaceInfo
	{
		size_t time;
		size_t distance;
	};

	class WaitForItPuzzle : public AoC::Puzzle
	{
	public:
		WaitForItPuzzle();
		~WaitForItPuzzle() = default;

	private:
		void SolvePartOne(const std::string& input);
		void SolvePartTwo(const std::string& input);
		void ParseRaceInfo(const std::vector<std::string>& lines);

		std::array<RaceInfo, 4> m_Races{};
	};
}