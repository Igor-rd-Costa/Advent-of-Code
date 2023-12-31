#pragma once

#include "Puzzle.h"

namespace AoC2023 {

	class TrebuchetPuzzle : public AoC::Puzzle
	{
	public:
		TrebuchetPuzzle();
		~TrebuchetPuzzle() = default;

		uint32_t FindNumberPartOne(std::string_view line);
		uint32_t FindNumberPartTwo(std::string_view line);

	private:
		virtual void SolvePartOne(const std::string& input) override;
		virtual void SolvePartTwo(const std::string& input) override;
		
		char ParseOne(std::string_view line, int& counter);
		char ParseTwo(std::string_view line, int& counter);
		char ParseThree(std::string_view line, int& counter);
		char ParseFour(std::string_view line, int& counter);
		char ParseFive(std::string_view line, int& counter);
		char ParseSix(std::string_view line, int& counter);
		char ParseSeven(std::string_view line, int& counter);
		char ParseEight(std::string_view line, int& counter);
		char ParseNine(std::string_view line, int& counter);
		size_t m_PartOneSum = 0;
		size_t m_PartTwoSum = 0;
	};

}