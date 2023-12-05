#pragma once
#include <string>
#include <array>

namespace AoC {

	class Puzzle;

	struct PuzzleInfo {
		uint32_t Day;
		std::string_view Name;
		Puzzle* (*Load)();
	};

	class Puzzle {
	public:
		~Puzzle() = default;
		static Puzzle* Load(std::string_view puzzleName);
		static Puzzle* Load(uint32_t puzzleDay);
		static void ListPuzzles();
	protected:
		Puzzle() = default;
		virtual void ShowInfo() = 0;
	private:
		static std::array<PuzzleInfo, 1> s_Puzzles;
	};
}