#include <iostream>
#include "IfYouGiveASeedAFertilizerPuzzle.h"
#include "Timer.h"

namespace AoC2023 {

	IfYouGiveASeedAFertilizerPuzzle::IfYouGiveASeedAFertilizerPuzzle() 
		: Puzzle("src/Day5/input", "src/Day5/info.txt")
	{
		std::string input = this->LoadInput();
		this->SolvePartOne(input);
		this->SolvePartTwo(input);
	}

	void IfYouGiveASeedAFertilizerPuzzle::SolvePartOne(const std::string& input)
	{
		AoC::Timer timer;
		std::vector<std::string> sections = this->GetSections(input);

		this->GetSeeds(sections[0]);

		this->ParseSectionsOne(sections);
		size_t smallest = m_Seeds[0];
		for (size_t seed : m_Seeds)
		{
			if (seed < smallest)
				smallest = seed;
		}
		long long time = timer.GetTime();
		std::cout << "Part one: " << smallest << " in " << time << "ms.\n";
	}

	void IfYouGiveASeedAFertilizerPuzzle::SolvePartTwo(const std::string& input)
	{
		AoC::Timer timer;
		std::vector<std::string> sections = this->GetSections(input);
		this->GetSeedRanges(sections[0]);
		this->ParseSectionsTwo(sections);

		const SeedRange* smallest = &m_SeedRanges[0];
		for (const SeedRange& seed : m_SeedRanges)
		{
			if (seed.start < smallest->start)
				smallest = &seed;
		}
		long long time = timer.GetTime();
		std::cout << "Part two: " << smallest->start << " in " << time << "ms.\n";
	}

	void IfYouGiveASeedAFertilizerPuzzle::GetSeedRanges(const std::string& input)
	{
		int count = 0;
		size_t start = input.find(':') + 1;
		size_t end = start;
		uint32_t index = 0;
		std::array<size_t, 2> range{};
		while (end < input.length())
		{
			while (input[start] == ' ')
				start++;

			end = start;
			while (end < input.length() && input[end] != ' ' && input[end] != '\n')
				end++;

			range[index] = std::stoull(input.substr(start, end - start));
			index++;
			
			if (index == 2)
			{
				m_SeedRanges.emplace_back(SeedRange{ range[0], range[1] });
				index = 0;
			}

			start = end;
		}
	}

	void IfYouGiveASeedAFertilizerPuzzle::ParseSectionsTwo(const std::vector<std::string>& sections)
	{
		for (uint32_t index = 1; index < sections.size(); index++)
		{
			std::vector<std::string> lines = this->SplitLines(sections[index]);
			std::vector<SeedRange> temp{};
			for (size_t i = 0; i < m_SeedRanges.size(); i++)
			{
				SeedRange& seedRange = m_SeedRanges[i];
				bool found = false;
				for (size_t j = 1; j < lines.size(); j++)
				{
					Range range = this->GetRangeFromLine(lines[j]);
					if (seedRange.start >= range.srcStart && seedRange.start < range.srcStart + range.length)
					{
						found = true;
						if ((seedRange.start + seedRange.length - 1) < range.srcStart + range.length)
						{
							temp.emplace_back(SeedRange{ range.dstStart + (seedRange.start - range.srcStart), seedRange.length});
							break;
						}
						else 
						{
							// Splits the range and inserts the part that falls outside 
							// of the destination range back into the src range to be parsed.
							SeedRange newRange = { seedRange.start, (range.srcStart + range.length) - seedRange.start };
							temp.emplace_back(SeedRange{ range.dstStart + (newRange.start - range.srcStart), newRange.length });
							m_SeedRanges.emplace_back(SeedRange{ 
								range.srcStart + range.length,(seedRange.start + seedRange.length) - (range.srcStart + range.length) 
							});
							break;
						}
					}
				}
				if (!found)
					temp.push_back(seedRange);

			}
			m_SeedRanges = temp;
		}
	}

	void IfYouGiveASeedAFertilizerPuzzle::GetSeeds(const std::string& input)
	{
		size_t start = input.find(':') + 1;
		size_t end = start;
		while (end < input.length())
		{
			while (input[start] == ' ')
				start++;

			end = start;
			while (end < input.length() && input[end] != ' ' && input[end] != '\n')
				end++;

			m_Seeds.emplace_back(std::stoull(input.substr(start, end - start)));

			start = end;
		}
	}

	void IfYouGiveASeedAFertilizerPuzzle::ParseSectionsOne(const std::vector<std::string>& sections)
	{
		for (size_t i = 1; i < sections.size(); i++)
		{
			std::vector<std::string> lines = this->SplitLines(sections[i]);
			
			std::vector<Range> ranges;
			for (size_t j = 1; j < lines.size(); j++)
			{
				ranges.emplace_back(GetRangeFromLine(lines[j]));
			}

			std::vector<size_t> temp{};
			temp.reserve(m_Seeds.size());
			for (size_t i = 0; i < m_Seeds.size(); i++)
			{
				bool found = false;
				for (const Range& range : ranges)
				{
					if (range.srcStart <= m_Seeds[i]  && m_Seeds[i] < range.srcStart + range.length)
					{
						temp.emplace_back(range.dstStart + (m_Seeds[i] - range.srcStart));
						found = true;
						break;
					}
				}

				if (!found)
				{
					temp.push_back(m_Seeds[i]);
				}
			}
			m_Seeds = temp;
		}
	}

	std::vector<std::string> IfYouGiveASeedAFertilizerPuzzle::GetSections(const std::string& input)
	{
		std::vector<std::string> sections;

		size_t start = 0;
		size_t end = 0;
		while (end < input.length())
		{
			end = input.find('\n', start);

			while (end != input.npos && input[end + 1] != '\n')
			{
				end = input.find('\n', end + 1);
			}

			if (end == input.npos)
			{
				end = input.length();
			}

			std::string section = input.substr(start, end - start);
			sections.push_back(section);

			start = end + 2;
		}
		return sections;
	}

	std::vector<std::string> IfYouGiveASeedAFertilizerPuzzle::SplitLines(const std::string& text)
	{
		std::vector<std::string> lines;

		size_t start = 0;
		size_t end = text.find('\n');
		if (end == text.npos)
		{
			lines.push_back(text);
			return lines;
		}
		
		while (end != text.npos)
		{
			std::string line = text.substr(start, end - start);
			lines.push_back(line);

			start = end + 1;
			end = text.find('\n', start);
		}

		if (end == text.npos)
		{	
			end = text.length();
			std::string line = text.substr(start, end - start);
			lines.push_back(line);
		}

		return lines;
	}

	Range IfYouGiveASeedAFertilizerPuzzle::GetRangeFromLine(const std::string& line)
	{
		std::array<size_t, 3> range{};
		int count = 0;
		for (size_t i = 0; i < line.length(); i++)
		{
			while (!std::isdigit(line[i]))
				i++;

			size_t start = i;
			
			while (std::isdigit(line[i]))
				i++;


			std::string number = line.substr(start, i - start);
			range[count % 3] = std::stoull(number);
			count++;
		}
		return { range[0], range[1], range[2] };
	}
}