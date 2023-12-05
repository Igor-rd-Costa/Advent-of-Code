#include <iostream>
#include "CubeConundrumPuzzle.h"
#include "Timer.h"

namespace AoC2023 {

	CubeConundrumPuzzle::CubeConundrumPuzzle()
		: Puzzle("src/Day2/input", "src/Day2/info.txt")
	{
		std::string input = this->LoadInput();
		std::cout << "Calculating result for " << this->m_InputFilePath << ".\n";
		this->SolvePartOne(input);
		this->SolvePartTwo(input);
	}

	void CubeConundrumPuzzle::SolvePartOne(const std::string& input)
	{
		AoC::Timer timer;
		uint32_t gameID = 1;
		uint32_t idSum = 0;
		uint32_t redCubes = 0;
		uint32_t greenCubes = 0;
		uint32_t blueCubes = 0;
		for (uint32_t i = 0; i < input.length(); i++)
		{
			if (input[i] == ';') // end round
			{
				redCubes = 0;
				greenCubes = 0;
				blueCubes = 0;
			}


			if (input[i] == '\n') // end game
			{
				if (redCubes != 0 || greenCubes != 0 || blueCubes != 0)
				{
					idSum += gameID;
				}
				gameID++;
			}

			if (input[i] == ':' || input[i] == ',' || input[i] == ';')
			{
				int numStart = ++i;
				int numEnd = input.find(' ', numStart + 1);
				uint32_t cubeCount = std::stoi(input.substr(numStart, numEnd - numStart));
				i = numEnd;
				if (input[i + 1] == 'r')
				{
					if (cubeCount > m_MaxRed)
					{
						redCubes = 0;
						greenCubes = 0;
						blueCubes = 0;
						while (input[i + 1] != '\n')
						{
							i++;
						}
						continue;
					}

					if (redCubes < cubeCount)
						redCubes = cubeCount;
					i += 3;
				}
				else if (input[i + 1] == 'g')
				{
					if (cubeCount > m_MaxGreen)
					{
						redCubes = 0;
						greenCubes = 0;
						blueCubes = 0;
						while (input[i + 1] != '\n')
						{
							i++;
						}
						continue;
					}

					if (greenCubes < cubeCount)
						greenCubes = cubeCount;
					i += 5;
				}
				else if (input[i + 1] == 'b')
				{
					if (cubeCount > m_MaxBlue)
					{
						redCubes = 0;
						greenCubes = 0;
						blueCubes = 0;
						while (input[i + 1] != '\n')
						{
							i++;
						}
						continue;
					}

					if (blueCubes < cubeCount)
						blueCubes = cubeCount;
					i += 4;
				}
			}
		}
		long long time = timer.GetTime();
		std::cout << "Part one: " << idSum << " in " << time << "ms.\n";
	}

	void CubeConundrumPuzzle::SolvePartTwo(const std::string& input)
	{
		AoC::Timer timer;
		uint32_t powerSum = 0;
		uint32_t minRed = 0, minGreen = 0, minBlue = 0;
		for (uint32_t i = 0; i < input.length(); i++)
		{
			if (input[i] == '\n') // end game
			{
				powerSum += (minRed * minGreen * minBlue);
				minRed = 0;
				minGreen = 0;
				minBlue = 0;
			}

			if (input[i] == ':' || input[i] == ',' || input[i] == ';')
			{
				int numStart = ++i;
				int numEnd = input.find(' ', numStart + 1);
				uint32_t cubeCount = std::stoi(input.substr(numStart, numEnd - numStart));
				i = numEnd;
				if (input[i + 1] == 'r')
				{
					if (minRed < cubeCount)
						minRed = cubeCount;
					i += 3;
				}
				else if (input[i + 1] == 'g')
				{
					if (minGreen < cubeCount)
						minGreen = cubeCount;
					i += 5;
				}
				else if (input[i + 1] == 'b')
				{
					if (minBlue < cubeCount)
						minBlue = cubeCount;
					i += 4;
				}
			}
		}
		long long time = timer.GetTime();
		std::cout << "Part two: " << powerSum << " in " << time << "ms.\n";
	}

}
