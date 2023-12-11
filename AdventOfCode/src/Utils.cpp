#include "Utils.h"

namespace AoC {

	std::vector<std::string> SplitLines(const std::string& text)
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

		if (end == text.npos && start < text.length())
		{
			end = text.length();
			std::string line = text.substr(start, end - start);
			lines.push_back(line);
		}

		return lines;
	}

}

