#include <vector>
#include <iostream>
#include "WaitForItPuzzle.h"
#include "Utils.h"
#include "Timer.h"

namespace AoC2023 {

	WaitForItPuzzle::WaitForItPuzzle()
		: Puzzle("src/Day6/input", "src/Day6/info.txt")
	{
		std::string input = this->LoadInput();

		this->SolvePartOne(input);
		this->SolvePartTwo(input);
	}

	void WaitForItPuzzle::SolvePartOne(const std::string& input)
	{
		AoC::Timer timer;
		std::vector<std::string> lines = AoC::SplitLines(input);

		this->ParseRaceInfo(lines);
		std::array<size_t, 4> results{};

		for (uint32_t i = 0; i < m_Races.size(); i++)
		{
			uint32_t count = 0;
			for (uint32_t j = 1; j < m_Races[i].time; j++)
			{
				if (j * (m_Races[i].time - j) > m_Races[i].distance)
					count++;
			}

			results[i] = count;
		}
		size_t result = results[0] * results[1] * results[2] * results[3];
		long long time = timer.GetTime();
		std::cout << "Part one: " << result << " in " << time << "ms.\n";
	}

	void WaitForItPuzzle::SolvePartTwo(const std::string& input)
	{
		AoC::Timer timer;
		std::vector<std::string> lines = AoC::SplitLines(input);

		size_t timeStart = lines[0].find(':');
		size_t distStart = lines[1].find(':');
		std::string timeString = "";
		std::string distString = "";
		for (uint32_t i = 0; i < 4; i++)
		{
			while (!std::isdigit(lines[0][timeStart]))
				timeStart++;
			while (!std::isdigit(lines[1][distStart]))
				distStart++;

			size_t timeEnd = timeStart;
			size_t distEnd = distStart;

			while (std::isdigit(lines[0][timeEnd]))
				timeEnd++;
			while (std::isdigit(lines[1][distEnd]))
				distEnd++;

			timeString += lines[0].substr(timeStart, timeEnd - timeStart);
			distString += lines[1].substr(distStart, distEnd - distStart);

			timeStart = timeEnd + 1;
			distStart = distEnd + 1;
		}

		size_t time = std::stoull(timeString);
		size_t distance = std::stoull(distString);

		uint32_t count = 0;
		for (uint32_t i = 1; i < time; i++)
		{
			if (i * (time - i) > distance)
				count++;
		}
		long long duration = timer.GetTime();
		std::cout << "Part two: " << count << " in " << duration << "ms.\n";
	}

	void WaitForItPuzzle::ParseRaceInfo(const std::vector<std::string>& lines)
	{
		const std::string& times = lines[0];
		const std::string& distances = lines[1];
		size_t timeEnd = 0, timeStart = times.find(':');
		size_t distEnd = 0, distStart = distances.find(':');

		for (uint32_t i = 0; i < 4; i++)
		{
			while (!std::isdigit(times[timeStart]))
				timeStart++;
			while (!std::isdigit(distances[distStart]))
				distStart++;

			timeEnd = timeStart;
			distEnd = distStart;

			while (std::isdigit(times[timeEnd]))
				timeEnd++;
			while (std::isdigit(distances[distEnd]))
				distEnd++;

			size_t time = std::stoull(times.substr(timeStart, timeEnd - timeStart));
			size_t distance = std::stoull(distances.substr(distStart, distEnd - distStart));

			m_Races[i] = { time, distance };

			timeStart = timeEnd + 1;
			distStart = distEnd + 1;
		}

	}

}
