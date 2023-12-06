#pragma once
#include "Puzzle.h"

namespace AoC2023 {

	class GearRatiosPuzzle : public AoC::Puzzle
	{
	public:
		GearRatiosPuzzle();
		~GearRatiosPuzzle() = default;

	private:
		void SolvePartOne(const std::string& input);
		void SolvePartTwo(const std::string& input);
		bool IsNumberNearSymbol(const std::string& input, int start, int length);
		uint32_t GetGearRation(const std::string& input, int index);
		bool IsSymbol(char character);

		int m_RowLength;
	};
}