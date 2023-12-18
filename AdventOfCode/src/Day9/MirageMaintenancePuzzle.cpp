#include <iostream>
#include "MirageMaintenancePuzzle.h"
#include "Timer.h"

namespace AoC2023 {

	MirageMaintenancePuzzle::MirageMaintenancePuzzle()
		: Puzzle("src/Day9/input", "src/Day9/info.txt")
	{
		m_Input = this->LoadInput();

		this->SolvePartOne(m_Input);
		this->SolvePartTwo(m_Input);
	}

	void MirageMaintenancePuzzle::SolvePartOne(const std::string& input)
	{
		AoC::Timer timer;
		size_t start = 0;
		size_t end = input.find('\n');

		long long sum = 0;
		while (end != input.npos)
		{
			std::string line = input.substr(start, end - start);
			std::vector<int> numbers{};
			while (start != end)
			{
				while (!std::isdigit(input[start]) && input[start] != '-')
					start++;

				size_t numEnd = start;
				while (std::isdigit(input[numEnd]) || input[numEnd] == '-')
					numEnd++;

				numbers.push_back(std::stoi(input.substr(start, numEnd - start)));

				start = numEnd;
			}

			sum += numbers[numbers.size() - 1] + this->GetNextValueSum(numbers);


			start = end + 1;
			end = input.find('\n', start);
		}
		long long time = timer.GetTime();
		std::cout << "Part one: " << sum << " in " << time << "ms.\n";
	}

	void MirageMaintenancePuzzle::SolvePartTwo(const std::string& input)
	{
		AoC::Timer timer;
		size_t start = 0;
		size_t end = input.find('\n');

		long long sum = 0;
		while (end != input.npos)
		{
			std::string line = input.substr(start, end - start);
			std::vector<int> numbers{};
			while (start != end)
			{
				while (!std::isdigit(input[start]) && input[start] != '-')
					start++;

				size_t numEnd = start;
				while (std::isdigit(input[numEnd]) || input[numEnd] == '-')
					numEnd++;

				numbers.push_back(std::stoi(input.substr(start, numEnd - start)));

				start = numEnd;
			}

			sum += numbers[0] - this->GetPreviousValueSum(numbers);


			start = end + 1;
			end = input.find('\n', start);
		}
		long long time = timer.GetTime();
		std::cout << "Part two: " << sum << " in " << time << "ms.\n";
	}

	int MirageMaintenancePuzzle::GetNextValueSum(const std::vector<int>& numbers)
	{
		std::vector<int> remainders{};
		remainders.reserve(numbers.size() - 1);
		for (size_t i = 0; i < numbers.size() - 1; i++)
		{
			remainders.push_back(numbers[i + 1] - numbers[i]);
		}

		bool isAllZeros = true;
		for (int number : remainders)
		{
			if (number != 0)
			{
				isAllZeros = false;
				break;
			}
		}

		if (isAllZeros)
			return 0;

		return remainders[remainders.size() - 1] + GetNextValueSum(remainders);
	}
	
	int MirageMaintenancePuzzle::GetPreviousValueSum(const std::vector<int>& numbers)
	{
		std::vector<int> remainders{};
		remainders.reserve(numbers.size() - 1);
		for (size_t i = 0; i < numbers.size() - 1; i++)
		{
			remainders.push_back(numbers[i + 1] - numbers[i]);
		}

		bool isAllZeros = true;
		for (int number : remainders)
		{
			if (number != 0)
			{
				isAllZeros = false;
				break;
			}
		}

		if (isAllZeros)
			return 0;

		return remainders[0] - GetPreviousValueSum(remainders);
	}
}
