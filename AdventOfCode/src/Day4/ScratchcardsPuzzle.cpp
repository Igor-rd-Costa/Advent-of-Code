#include <iostream>
#include <array>
#include <unordered_map>
#include "ScratchcardsPuzzle.h"
#include "Timer.h"

namespace AoC2023 {

	ScratchcardsPuzzle::ScratchcardsPuzzle()
		: Puzzle("src/Day4/input", "src/Day4/info.txt")
	{
		std::string input = this->LoadInput();
		this->SolvePartOne(input);
		this->SolvePartTwo(input);

	}

	void ScratchcardsPuzzle::SolvePartOne(const std::string& input)
	{
		AoC::Timer timer;
		size_t pointSum = 0;
		for (size_t i = 0; i < input.length(); i++)
		{
			if (input[i] == ':')
			{
				i++;
				std::array<uint32_t, 10> winningNumbers{};
				std::array<uint32_t, 25> cardNumbers{};
				size_t points = 0;
				size_t winNumEnd = input.find('|', i) - 1;
				size_t numStart = winNumEnd + 2;
				size_t numEnd = input.find('\n', numStart);

				// Get winning numbers
				uint32_t index = 0;
				while (i < winNumEnd)
				{
					while (input[i] == ' ')
						i++;

					size_t start = i;
					while (input[i] != ' ')
						i++;

					if (index < 10)
					{
						winningNumbers[index] = std::stoi(input.substr(start, i - start));
						index++;
					}
				}

				i = numStart;
				index = 0;
				// get card numbers
				while (i < numEnd)
				{
					while (input[i] == ' ')
						i++;

					size_t start = i;
					while (input[i] != ' ' && input[i] != '\n')
						i++;

					if (index < 25)
					{
						cardNumbers[index] = std::stoi(input.substr(start, i - start));
						index++;
					}
				}

				for (uint32_t winningNumber : winningNumbers)
				{
					for (uint32_t cardNumber : cardNumbers)
					{
						if (winningNumber == cardNumber)
						{
							if (points == 0)
								points++;
							else
								points *= 2;

							continue;
						}
					}
				}

				pointSum += points;

				i = numEnd + 1;
			}
		}

		long long time = timer.GetTime();
		std::cout << "Part one: " << pointSum << " in " << time << "ms.\n";
	}

	void ScratchcardsPuzzle::SolvePartTwo(const std::string& input)
	{
		AoC::Timer timer;
		size_t cardSum = 0;
		uint32_t cardId = 0;
		std::unordered_map<uint32_t, uint32_t> cards;
		for (size_t i = 0; i < input.length(); i++)
		{
			if (input[i] == ':')
			{
				i++;
				cardId++;
				cards[cardId]++;
				std::array<uint32_t, 10> winningNumbers{};
				std::array<uint32_t, 25> cardNumbers{};
				size_t matchingCards = 0;
				size_t winNumEnd = input.find('|', i) - 1;
				size_t numStart = winNumEnd + 2;
				size_t numEnd = input.find('\n', numStart);

				// Get winning numbers
				uint32_t index = 0;
				while (i < winNumEnd)
				{
					while (input[i] == ' ')
						i++;

					size_t start = i;
					while (input[i] != ' ')
						i++;

					if (index < 10)
					{
						winningNumbers[index] = std::stoi(input.substr(start, i - start));
						index++;
					}
				}

				i = numStart;
				index = 0;
				// get card numbers
				while (i < numEnd)
				{
					while (input[i] == ' ')
						i++;

					size_t start = i;
					while (input[i] != ' ' && input[i] != '\n')
						i++;

					if (index < 25)
					{
						cardNumbers[index] = std::stoi(input.substr(start, i - start));
						index++;
					}
				}

				for (uint32_t winningNumber : winningNumbers)
				{
					for (uint32_t cardNumber : cardNumbers)
					{
						if (winningNumber == cardNumber)
						{
							matchingCards++;
							continue;
						}
					}
				}

				for (uint32_t j = 1; j <= matchingCards; j++)
				{
					cards[cardId + j] += cards[cardId];
				}

				i = numEnd + 1;
			}
		}

		for (auto& pair : cards)
		{
			cardSum += pair.second;
		}

		long long time = timer.GetTime();
		std::cout << "Part two: " << cardSum << " in " << time << "ms.\n";
	}

}
