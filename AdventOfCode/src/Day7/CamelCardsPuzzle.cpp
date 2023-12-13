
#include <bitset>
#include <iostream>
#include <algorithm>
#include "CamelCardsPuzzle.h"
#include "Timer.h"



namespace AoC2023 {

	const uint32_t CARD_TYPE_BITS = 15;

	CamelCardsPuzzle::CamelCardsPuzzle()
		: Puzzle("src/Day7/input", "src/Day7/info.txt")
	{
		std::string input = this->LoadInput();

		this->SolvePartOne(input);
		this->SolvePartTwo(input);
	}

	void CamelCardsPuzzle::SolvePartOne(const std::string& input)
	{
		AoC::Timer timer;
		size_t start = 0;
		size_t end = input.find('\n');

		while (end != input.length() && end != input.npos)
		{
			size_t space = input.find(' ', start);
			std::string hand = input.substr(start, space - start);
			std::string bid = input.substr(space + 1, end - space - 1);

			HandInfo& handInfo = m_Hands.emplace_back(HandInfo{ {}, this->ParseHandTypeOne(hand), std::stoi(bid)});
			memcpy(&handInfo.hand, hand.c_str(), 5);

			start = end + 1;
			end = input.find('\n', start);
		}

		this->SortHandsOne();

		size_t result = 0;
		size_t rank = m_Hands.size();
		for (uint32_t i = 0; i < m_Hands.size(); i++, rank--)
		{
			result += m_Hands[i].bid * rank;
		}
		long long time = timer.GetTime();
		std::cout << "Part one: " << result << " in " << time << "ms.\n";
		m_Hands.clear();
	}

	void CamelCardsPuzzle::SolvePartTwo(const std::string& input)
	{
		AoC::Timer timer;
		size_t start = 0;
		size_t end = input.find('\n');

		while (end != input.length() && end != input.npos)
		{
			size_t space = input.find(' ', start);
			std::string hand = input.substr(start, space - start);
			std::string bid = input.substr(space + 1, end - space - 1);

			HandInfo& handInfo = m_Hands.emplace_back(HandInfo{ {}, this->ParseHandTypeTwo(hand), std::stoi(bid) });
			memcpy(&handInfo.hand, hand.c_str(), 5);

			start = end + 1;
			end = input.find('\n', start);
		}

		this->SortHandsTwo();

		size_t result = 0;
		size_t rank = m_Hands.size();
		for (uint32_t i = 0; i < m_Hands.size(); i++, rank--)
		{
			result += m_Hands[i].bid * rank;
		}
		long long time = timer.GetTime();
		std::cout << "Part two: " << result << " in " << time << "ms.\n";
	}

	HandType CamelCardsPuzzle::ParseHandTypeOne(const std::string& hand)
	{
		CardInfo info[5]{};

		int cardCount = 0;
		for (char card : hand)
		{
			char cardType = CamelCardsPuzzle::GetCardTypeOne(card);

			for (uint32_t i = 0; i < 5; i++)
			{
				if (info[i] == 0)
				{
					info[i] = cardType + (1 << 4);
					cardCount++;
					break;
				}

				if ((info[i] & CARD_TYPE_BITS) == cardType)
				{
					info[i] += (1 << 4);
					break;
				}
			}
		}

		if (cardCount == 1)
			return FIVE_KIND;

		if (cardCount == 4)
			return ONE_PAIR;

		if (cardCount == 5)
			return HIGH_CARD;
		
		if (cardCount == 2)
		{
			if ((info[0] >> 4) == 1 || (info[0] >> 4) == 4)
				return FOUR_KIND;


			return FULL_HOUSE;
		}

		bool hasThreeOfSameLabel = false;
		if (cardCount == 3)
		{
			for (uint32_t i = 0; i < 3; i++)
			{
				if ((info[i] >> 4) == 3) 
				{
					hasThreeOfSameLabel = true;
					break;
				}
			}
		}

		if (hasThreeOfSameLabel)
			return THREE_KIND;
		return TWO_PAIR;
	}

	char CamelCardsPuzzle::GetCardTypeOne(char card)
	{
		if (card <= '9')
		{
			return card - 50;
		}
		else
		{
			switch (card)
			{
			case 'T': {
				return 8;
			} break;
			case 'J': {
				return 9;
			} break;
			case 'Q': {
				return 10;
			} break;
			case 'K': {
				return 11;
			} break;
			case 'A': {
				return 12;
			} break;
			default: {
				return 0;
			} break;
			}
		}
	}

	void CamelCardsPuzzle::SortHandsOne()
	{
		std::sort(m_Hands.begin(), m_Hands.end(), [](HandInfo& a, HandInfo& b) {

			if (a.type > b.type)
				return true;

			if (a.type < b.type)
				return false;

			for (uint32_t i = 0; i < 5; i++)
			{
				char aType = CamelCardsPuzzle::GetCardTypeOne(a.hand[i]);
				char bType = CamelCardsPuzzle::GetCardTypeOne(b.hand[i]);

				if (aType > bType)
					return true;

				if (aType < bType)
					return false;
			}

			return true;
		});
	}


	HandType CamelCardsPuzzle::ParseHandTypeTwo(const std::string& hand)
	{
		CardInfo info[5]{};

		int cardCount = 0;
		for (char card : hand)
		{
			char cardType = CamelCardsPuzzle::GetCardTypeTwo(card);

			for (uint32_t i = 0; i < 5; i++)
			{
				if (info[i] == 0)
				{
					info[i] = cardType + (1 << 4);
					cardCount++;
					break;
				}

				if ((info[i] & CARD_TYPE_BITS) == cardType)
				{
					info[i] += (1 << 4);
					break;
				}
			}
		}

		if (cardCount == 1)
			return FIVE_KIND;

		uint32_t jokerCount = this->CountJokers(info);

		if (cardCount == 4)
		{
			if (jokerCount > 0)
			{
				return THREE_KIND;
			}

			return ONE_PAIR;
		}

		if (cardCount == 5)
		{
			if (jokerCount > 0)
				return ONE_PAIR;

			return HIGH_CARD;
		}

		if (cardCount == 2)
		{
			if (jokerCount > 0)
				return FIVE_KIND;

			if ((info[0] >> 4) == 1 || (info[0] >> 4) == 4)
				return FOUR_KIND;

			return FULL_HOUSE;
		}

		bool hasThreeOfSameLabel = false;
		if (cardCount == 3)
		{
			for (uint32_t i = 0; i < 3; i++)
			{
				if ((info[i] >> 4) == 3)
				{
					hasThreeOfSameLabel = true;
					break;
				}
			}
		}

		if (hasThreeOfSameLabel)
		{
			if (jokerCount > 0)
				return FOUR_KIND;

			return THREE_KIND;
		}

		if (jokerCount == 1)
			return FULL_HOUSE;

		if (jokerCount == 2)
			return FOUR_KIND;

		return TWO_PAIR;
	}

	char CamelCardsPuzzle::GetCardTypeTwo(char card)
	{
		if (card <= '9')
		{
			return card - 49;
		}
		else
		{
			switch (card)
			{
			case 'J': {
				return 0;
			} break;
			case 'T': {
				return 9;
			} break;
			case 'Q': {
				return 10;
			} break;
			case 'K': {
				return 11;
			} break;
			case 'A': {
				return 12;
			} break;
			default: {
				return 0;
			} break;
			}
		}
	}

	void CamelCardsPuzzle::SortHandsTwo()
	{
		std::sort(m_Hands.begin(), m_Hands.end(), [](HandInfo& a, HandInfo& b) {

			if (a.type > b.type)
				return true;

			if (a.type < b.type)
				return false;

			for (uint32_t i = 0; i < 5; i++)
			{
				char aType = CamelCardsPuzzle::GetCardTypeTwo(a.hand[i]);
				char bType = CamelCardsPuzzle::GetCardTypeTwo(b.hand[i]);

				if (aType > bType)
					return true;

				if (aType < bType)
					return false;
			}

			return true;
		});
	}

	uint32_t CamelCardsPuzzle::CountJokers(CardInfo* info)
	{
		for (uint32_t i = 0; i < 5; i++)
		{

			if (info[i] == 0)
				break;

			if ((info[i] & CARD_TYPE_BITS) == 0)
				return (info[i] >> 4);
		}

		return 0;
	}

}