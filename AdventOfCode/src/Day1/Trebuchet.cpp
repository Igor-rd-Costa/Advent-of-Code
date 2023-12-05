#include <fstream>
#include <iostream>
#include <vector>
#include "Trebuchet.h"
#include "Timer.h"

namespace AoC2023 {

	TrebuchetPuzzle::TrebuchetPuzzle()
	{
		this->ShowInfo();
		std::ifstream file(this->s_InputFilePath.data(), std::ios_base::ate);
		if (!file.is_open()) {
			std::cout << "[Puzzle Error] Failed to open " << this->s_InputFilePath << ".\n";
			return;
		}
		size_t inputSize = file.tellg();
		file.seekg(0);
		std::string input(inputSize, 0);
		file.read(input.data(), inputSize);
		file.close();

		std::cout << "Calculating result for " << this->s_InputFilePath << ".\n";
		AoC::Timer timer;
		size_t start = 0;
		size_t end = input.find('\n');
		size_t sum = 0;
		while (end != input.npos)
		{
			std::string_view line(input.data() + start, end - start);

			m_PartOneSum += FindNumberPartOne(line);

			start = end + 1;
			end = input.find('\n', start);
		}
		long long time = timer.GetTime();
		std::cout << "Part One: " << m_PartOneSum << " in " << time << "ms.\n";

		start = 0;
		end = input.find('\n');
		sum = 0;
		while (end != input.npos)
		{
			std::string_view line(input.data() + start, end - start);
			m_PartTwoSum += FindNumberPartTwo(line);
			start = end + 1;
			end = input.find('\n', start);
		}
		time = timer.GetTime();
		std::cout << "Part Two: " << m_PartTwoSum << " in " << time << "ms.\n";
	}

	uint32_t TrebuchetPuzzle::FindNumberPartOne(std::string_view line)
	{
		std::string values(2, 0);
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] >= '0' && line[i] <= '9')
			{
				if (values[0] == 0)
				{
					values[0] = line[i];
					values[1] = line[i];
				}
				else 
				{
					values[1] = line[i];
				}
			}
		}
		return std::stoi(values);
	}

	uint32_t TrebuchetPuzzle::FindNumberPartTwo(std::string_view line)
	{
		std::string values(2, 0);
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] >= '0' && line[i] <= '9')
			{
				if (values[0] == 0)
				{
					values[0] = line[i];
					values[1] = line[i];
				}
				else
				{
					values[1] = line[i];
				}
			}
			else {
				if (line[i] == 'o')
				{
					if (line.length() - i < 3)
						continue;

					char result = ParseOne(line, i);
					if (result != 0)
					{
						if (values[0] == 0)
						{
							values[0] = result;
							values[1] = result;
						}
						else
						{
							values[1] = result;
						}
					}
				}
				else if (line[i] == 't')
				{
					if (line.length() - i < 3)
						continue;

					char result = ParseTwo(line, i);
					if (result != 0)
					{
						if (values[0] == 0)
						{
							values[0] = result;
							values[1] = result;
						}
						else
						{
							values[1] = result;
						}
					}
				}
				else if (line[i] == 'f')
				{
					if (line.length() - i < 4)
						continue;

					char result = ParseFour(line, i);
					if (result != 0)
					{
						if (values[0] == 0)
						{
							values[0] = result;
							values[1] = result;
						}
						else
						{
							values[1] = result;
						}
					}
				}
				else if (line[i] == 's')
				{
					if (line.length() - i < 3)
						continue;

					char result = ParseSix(line, i);
					if (result != 0)
					{
						if (values[0] == 0)
						{
							values[0] = result;
							values[1] = result;
						}
						else
						{
							values[1] = result;
						}
					}
				}
				else if (line[i] == 'e')
				{
					if (line.length() - i < 5)
						continue;

					char result = ParseEight(line, i);
					if (result != 0)
					{
						if (values[0] == 0)
						{
							values[0] = result;
							values[1] = result;
						}
						else
						{
							values[1] = result;
						}
					}
				}
				else if (line[i] == 'n')
				{
					if (line.length() - i < 4)
						continue;

					char result = ParseNine(line, i);
					if (result != 0)
					{
						if (values[0] == 0)
						{
							values[0] = result;
							values[1] = result;
						}
						else
						{
							values[1] = result;
						}
					}
				}
			}
		}
		return std::stoi(values);
	}

	void TrebuchetPuzzle::ShowInfo()
	{
		std::ifstream file(this->s_InfoFilePath.data(), std::ios_base::ate);
		if (!file.is_open()) {
			std::cout << "[Puzzle Error] Failed to open " << this->s_InfoFilePath << ".\n";
			return;
		}
		size_t infoSize = file.tellg();
		file.seekg(0);
		std::string info(infoSize, 0);
		file.read(info.data(), infoSize);
		file.close();

		std::cout << info << "\n\n";
	}

	char TrebuchetPuzzle::ParseOne(std::string_view line, int& counter)
	{
		//line[counter] == 'o'
		if (line[counter + 1] == 'n')
		{
			counter++;
			if (line[counter + 1] == 'e')
			{
				counter++;
				return '1';
			}
			else
				return this->ParseNine(line, counter);
		}
		return 0;
	}

	char TrebuchetPuzzle::ParseTwo(std::string_view line, int& counter)
	{
		//line[counter] == 't'
		if (line[counter + 1] == 'w' && line[counter + 2] == 'o')
		{
			counter += 2;
			return '2';
		}

		return this->ParseThree(line, counter);
	}

	char TrebuchetPuzzle::ParseThree(std::string_view line, int& counter)
	{
		//line[counter] == 't'
		if (line[counter + 1] == 'h' && line[counter + 2] == 'r' && line[counter + 3] == 'e')
		{
			counter += 3;
			if (line[counter + 1] == 'e')
				return '3';
			else
				return this->ParseEight(line, counter);
		}
		return 0;
	}

	char TrebuchetPuzzle::ParseFour(std::string_view line, int& counter)
	{
		//line[counter] == 'f'
		if (line[counter + 1] == 'o')
		{
			counter++;
			if (line[counter + 1] == 'u')
			{
				counter++;
				if (line[counter + 1] == 'r')
				{
					counter++;
					return '4';
				}
			}
			else
			{
				return ParseOne(line, counter);
			}
		}
		return this->ParseFive(line, counter);
	}

	char TrebuchetPuzzle::ParseFive(std::string_view line, int& counter)
	{
		//line[counter] == 'f'
		if (line[counter + 1] == 'i' && line[counter + 2] == 'v' && line[counter + 3] == 'e')
		{
			counter += 3;
			return '5';
		}
		return 0;
	}

	char TrebuchetPuzzle::ParseSix(std::string_view line, int& counter)
	{
		//line[counter] == 's'
		if (line[counter + 1] == 'i' && line[counter + 2] == 'x')
		{
			counter += 2;
			return '6';
		}

		return this->ParseSeven(line, counter);
	}

	char TrebuchetPuzzle::ParseSeven(std::string_view line, int& counter)
	{
		//line[counter] == 's'
		if (line[counter + 1] == 'e')
		{
			counter++;
			if (line[counter + 1] == 'v')
			{
				counter++;
				if (line[counter + 1] == 'e')
				{
					counter++;
					if (line[counter + 1] == 'n')
					{
						counter++;
						return '7';
					}

					return this->ParseEight(line, counter);
				}
			}
			else
				return this->ParseEight(line, counter);
		}
		return 0;
	}

	char TrebuchetPuzzle::ParseEight(std::string_view line, int& counter)
	{
		//line[counter] == 'e'
		if (line[counter + 1] == 'i' && line[counter + 2] == 'g'
			&& line[counter + 3] == 'h' && line[counter + 4] == 't')
		{
			counter += 4;
			return '8';
		}
		return 0;
	}

	char TrebuchetPuzzle::ParseNine(std::string_view line, int& counter)
	{
		//line[counter] == 'n'
		if (line[counter + 1] == 'i' && line[counter + 2] == 'n')
		{
			counter += 2;
			if (line[counter + 1] == 'e')
			{
				counter++;
				return '9';
			}
			else
				return this->ParseNine(line, counter);
		}
		return 0;
	}
}