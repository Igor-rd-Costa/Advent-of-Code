#pragma once
#include <vector>
#include "Puzzle.h"

enum HandType : char {
	HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_KIND, FULL_HOUSE, FOUR_KIND, FIVE_KIND
};


struct HandInfo
{
	char hand[5];
	HandType type;
	int bid;
};

typedef uint32_t CardInfo;

namespace AoC2023 {

	class CamelCardsPuzzle : public AoC::Puzzle
	{
	public:
		CamelCardsPuzzle();
		~CamelCardsPuzzle() = default;

		static char GetCardTypeOne(char card);
		static char GetCardTypeTwo(char card);
	private:
		virtual void SolvePartOne(const std::string& input) override;
		virtual void SolvePartTwo(const std::string& input) override;
		
		HandType ParseHandTypeOne(const std::string& hand);
		void SortHandsOne();

		HandType ParseHandTypeTwo(const std::string& hand);
		uint32_t CountJokers(CardInfo* info);
		void SortHandsTwo();


		std::vector<HandInfo> m_Hands;
	};
}
