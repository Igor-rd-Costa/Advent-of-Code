#pragma once

#include "Puzzle.h"

namespace AoC2023 {

	class CubeConundrumPuzzle : public AoC::Puzzle
	{
	public:
		CubeConundrumPuzzle();
		~CubeConundrumPuzzle() = default;

	private:
		void SolvePartOne(const std::string& input);
		void SolvePartTwo(const std::string& input);

		const uint32_t m_MaxRed = 12;
		const uint32_t m_MaxGreen = 13;
		const uint32_t m_MaxBlue = 14;
	};

}