#pragma once
#include "Puzzle.h"

namespace AoC2023 {

	class ScratchcardsPuzzle : public AoC::Puzzle
	{
	public:
		ScratchcardsPuzzle();
		~ScratchcardsPuzzle() = default;

	private:
		void SolvePartOne(const std::string& input);
		void SolvePartTwo(const std::string& input);
	};
}