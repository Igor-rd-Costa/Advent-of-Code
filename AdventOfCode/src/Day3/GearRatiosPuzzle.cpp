#include <iostream>
#include "GearRatiosPuzzle.h"
#include "Timer.h"

namespace AoC2023 {

	static bool TryAddNumber(std::array<int, 2>& numArray, int number);

	GearRatiosPuzzle::GearRatiosPuzzle()
		: Puzzle("src/Day3/input", "src/Day3/info.txt")
	{
		std::string input = this->LoadInput();
		m_RowLength = input.find('\n') + 1; // all lines in input have the same length
		this->SolvePartOne(input);
		this->SolvePartTwo(input);
	}

	void GearRatiosPuzzle::SolvePartOne(const std::string& input)
	{
		AoC::Timer timer;
		uint32_t partSum = 0;

		for (int i = 0; i < input.length(); i++)
		{
			if (std::isdigit(input[i]))
			{
				int numStart = i;
				while (std::isdigit(input[i]))
				{
					i++;
				}
				uint32_t number = (uint32_t)std::stoi(input.substr(numStart, i - numStart));
				if (this->IsNumberNearSymbol(input, numStart - 1, i + 1))
				{
					partSum += number;
				}
			}
		}
		long long time = timer.GetTime();
		std::cout << "Part one: " << partSum << " in " << time << "ms.\n";
	}

	void GearRatiosPuzzle::SolvePartTwo(const std::string& input)
	{
		AoC::Timer timer;
		uint32_t gearRatio = 0;
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] == '*')
			{
				gearRatio += GetGearRation(input, i);
			}
		}
		long long time = timer.GetTime();
		std::cout << "Part two: " << gearRatio << " in " << time << "ms.\n";
	}

	bool GearRatiosPuzzle::IsNumberNearSymbol(const std::string& input, int start, int end)
	{
		for (int i = end; i > start; i--)
		{
			if ((i - (int)m_RowLength) >= 0)
			{
				if (this->IsSymbol(input[i - m_RowLength - 1]))
					return true;
			}
		}

		if (this->IsSymbol(input[start]) || this->IsSymbol(input[end - 1]))
			return true;

		for (int i = start; i < end; i++)
		{
			if ((i + m_RowLength) < input.length() && this->IsSymbol(input[i + m_RowLength]))
			{
				return true;
			}
		}
		return false;
	}

	uint32_t GearRatiosPuzzle::GetGearRation(const std::string& input, int index)
	{
		std::array<int, 2> numbers = { -1, -1 };

		if (std::isdigit(input[index - 1]))
		{
			int numEnd = index;
			int numStart = numEnd;
			while (std::isdigit(input[numStart - 1]))
			{
				numStart--;
			}
			int number = std::stoi(input.substr(numStart, numEnd - numStart));
			if (!TryAddNumber(numbers, number))
				return 0;
		}

		if (std::isdigit(input[index + 1]))
		{
			int numStart = index + 1;
			int numEnd = numStart;
			while (std::isdigit(input[numEnd]))
			{
				numEnd++;
			}
			int number = std::stoi(input.substr(numStart, numEnd - numStart));
			if (!TryAddNumber(numbers, number))
				return 0;
		}

		for (size_t i = (index - m_RowLength - 1); i < (index - m_RowLength - 1) + 3; i++)
		{

			if (std::isdigit(input[i]))
			{
				size_t strStart = i;
				while (std::isdigit(input[strStart - 1]))
				{
					strStart--;
				}
				while (std::isdigit(input[i]))
				{
					i++;
				}
				int number = std::stoi(input.substr(strStart, i - strStart));
				if (!TryAddNumber(numbers, number))
					return 0;
			}
		}

		for (size_t i = (index + m_RowLength - 1); i < (index + m_RowLength - 1) + 3; i++)
		{
			if (std::isdigit(input[i]))
			{
				size_t strStart = i;
				while (std::isdigit(input[strStart - 1]))
				{
					strStart--;
				}
				while (std::isdigit(input[i]))
				{
					i++;
				}
				int number = std::stoi(input.substr(strStart, i - strStart));
				if (!TryAddNumber(numbers, number))
				{
					return 0;
				}
			}
		}

		if (numbers[0] != -1 && numbers[1] != -1)
		{
			return numbers[0] * numbers[1];
		}
		return 0;
	}

	static bool TryAddNumber(std::array<int, 2>& numArray, int number)
	{
		if (numArray[0] == -1)
		{
			numArray[0] = number;
		}
		else if (numArray[1] == -1)
		{
			numArray[1] = number;
		}
		else
		{
			return false;
		}

		return true;
	}

	bool GearRatiosPuzzle::IsSymbol(char character)
	{
		if (character != '.' && std::ispunct(character))
		{
			return true;
		}

		return false;
	}
}
