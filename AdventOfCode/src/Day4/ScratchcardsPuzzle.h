#pragma once
#include "Puzzle.h"

namespace AoC2023 {

	class ScratchcardsPuzzle : public AoC::Puzzle
	{
	public:
		ScratchcardsPuzzle();
		~ScratchcardsPuzzle() = default;

	private:
		virtual void SolvePartOne(const std::string& input) override;
		virtual void SolvePartTwo(const std::string& input) override;
	};
}