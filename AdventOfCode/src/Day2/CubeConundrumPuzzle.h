#pragma once

#include "Puzzle.h"

namespace AoC2023 {

	class CubeConundrumPuzzle : public AoC::Puzzle
	{
	public:
		CubeConundrumPuzzle();
		~CubeConundrumPuzzle() = default;

	private:
		virtual void SolvePartOne(const std::string& input) override; 
		virtual void SolvePartTwo(const std::string& input) override; 

		const uint32_t m_MaxRed = 12;
		const uint32_t m_MaxGreen = 13;
		const uint32_t m_MaxBlue = 14;
	};

}