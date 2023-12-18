#pragma once
#include "Puzzle.h"

namespace AoC2023 {

	class GearRatiosPuzzle : public AoC::Puzzle
	{
	public:
		GearRatiosPuzzle();
		~GearRatiosPuzzle() = default;

	private:
		virtual void SolvePartOne(const std::string& input) override;
		virtual void SolvePartTwo(const std::string& input) override;

		bool IsNumberNearSymbol(const std::string& input, int start, int length);
		uint32_t GetGearRation(const std::string& input, int index);
		bool IsSymbol(char character);

		size_t m_RowLength;
	};
}