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

		std::string LoadInput();
		
		static Puzzle* Load(std::string_view puzzleName);
		static Puzzle* Load(uint32_t puzzleDay);
		static void ListPuzzles();
		
	protected:
		Puzzle(std::string_view inputPath, std::string_view infoPath);
		void ShowInfo();
		const std::string_view m_InputFilePath;
		const std::string_view m_InfoFilePath;
	private:
		static std::array<PuzzleInfo, 7> s_Puzzles;
	};
}