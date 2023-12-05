#include <iostream>
#include "Puzzle.h"
#include "Day1/Trebuchet.h"

namespace AoC {

	std::array<PuzzleInfo, 1> Puzzle::s_Puzzles = {
		{1, "Trebuchet", []() { return reinterpret_cast<Puzzle*>(new AoC2023::TrebuchetPuzzle()); }}
	};

	Puzzle* Puzzle::Load(std::string_view puzzleName)
	{
		for (PuzzleInfo& puzzle : Puzzle::s_Puzzles)
		{
			if (puzzle.Name == puzzleName) {
				return puzzle.Load();
			}
		}
		return nullptr;
	}

	Puzzle* Puzzle::Load(uint32_t puzzleDay)
	{
		for (PuzzleInfo& puzzle : Puzzle::s_Puzzles)
		{
			if (puzzle.Day == puzzleDay) {
				return puzzle.Load();
			}
		}
		return nullptr;
	}

	void Puzzle::ListPuzzles()
	{
		for (PuzzleInfo& puzzle : Puzzle::s_Puzzles)
		{
			std::cout << puzzle.Day << ". " << puzzle.Name << ";\n";
		}
	}

	void Puzzle::ShowInfo()
	{

	}
}