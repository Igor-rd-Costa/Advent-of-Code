#pragma once
#include "Puzzle.h"
#include <vector>

namespace AoC2023 {

	class MirageMaintenancePuzzle : public AoC::Puzzle
	{
	public:
		MirageMaintenancePuzzle();
		~MirageMaintenancePuzzle() = default;

	private:
		virtual void SolvePartOne(const std::string& input) override;
		virtual void SolvePartTwo(const std::string& input) override;
		int GetNextValueSum(const std::vector<int>& numbers);
		int GetPreviousValueSum(const std::vector<int>& numbers);

		std::string m_Input = "";
	};
}