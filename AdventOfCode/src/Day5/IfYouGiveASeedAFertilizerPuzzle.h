#pragma once
#include <vector>
#include "Puzzle.h"

namespace AoC2023 {

	struct Range
	{
		size_t dstStart;
		size_t srcStart;
		size_t length;
	};

	struct SeedRange
	{
		size_t start;
		size_t length;
	};

	class IfYouGiveASeedAFertilizerPuzzle : public AoC::Puzzle
	{
	public:
		IfYouGiveASeedAFertilizerPuzzle();
		~IfYouGiveASeedAFertilizerPuzzle() = default;

	private:
		virtual void SolvePartOne(const std::string& input) override;
		virtual void SolvePartTwo(const std::string& input) override;
		
		void GetSeeds(const std::string& input);
		void ParseSectionsOne(const std::vector<std::string>& sections);

		void GetSeedRanges(const std::string& input);
		void ParseSectionsTwo(const std::vector<std::string>& sections);
		
		std::vector<std::string> GetSections(const std::string& input);
		Range GetRangeFromLine(const std::string& line);
		std::vector<size_t> m_Seeds{};
		std::vector<SeedRange> m_SeedRanges;
	};
}