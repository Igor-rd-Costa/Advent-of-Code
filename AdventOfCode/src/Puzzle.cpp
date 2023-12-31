#include <iostream>
#include <fstream>
#include "Puzzle.h"
#include "Day1/TrebuchetPuzzle.h"
#include "Day2/CubeConundrumPuzzle.h"
#include "Day3/GearRatiosPuzzle.h"
#include "Day4/ScratchcardsPuzzle.h"
#include "Day5/IfYouGiveASeedAFertilizerPuzzle.h"
#include "Day6/WaitForItPuzzle.h"
#include "Day7/CamelCardsPuzzle.h"
#include "Day8/HauntedWastelandPuzzle.h"
#include "Day9/MirageMaintenancePuzzle.h"


namespace AoC {

	std::array<PuzzleInfo, 9> Puzzle::s_Puzzles = {
		{
			{ 1, "Trebuchet", []() { return reinterpret_cast<Puzzle*>(new AoC2023::TrebuchetPuzzle()); } },
			{ 2, "Cube Conundrum", []() { return reinterpret_cast<Puzzle*>(new AoC2023::CubeConundrumPuzzle()); } },
			{ 3, "Gear Ratios", []() { return reinterpret_cast<Puzzle*>(new AoC2023::GearRatiosPuzzle()); } },
			{ 4, "Scratchcards", []() { return reinterpret_cast<Puzzle*>(new AoC2023::ScratchcardsPuzzle()); } },
			{ 5, "If You Give a Seed a Fertilizer", []() { return reinterpret_cast<Puzzle*>(new AoC2023::IfYouGiveASeedAFertilizerPuzzle()); } },
			{ 6, "Wait For It", []() { return reinterpret_cast<Puzzle*>(new AoC2023::WaitForItPuzzle()); } },
			{ 7, "Camel Cards", []() { return reinterpret_cast<Puzzle*>(new AoC2023::CamelCardsPuzzle()); } },
			{ 8, "Haunted Wasteland", []() { return reinterpret_cast<Puzzle*>(new AoC2023::HauntedWastelandPuzzle()); } },
			{ 9, "Mirage Maintenance", []() { return reinterpret_cast<Puzzle*>(new AoC2023::MirageMaintenancePuzzle()); } }
		}
	};


	Puzzle::Puzzle(std::string_view inputPath, std::string_view infoPath)
		: m_InputFilePath(inputPath), m_InfoFilePath(infoPath)
	{
		this->ShowInfo();
	}

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

	void Puzzle::ShowInfo()
	{
		std::ifstream file(this->m_InfoFilePath.data(), std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			std::cout << "[Puzzle Error] Failed to open " << this->m_InfoFilePath << ".\n";
			return;
		}
		size_t infoSize = file.tellg();
		file.seekg(0);
		std::string info(infoSize, 'a');
		file.read(info.data(), infoSize);
		file.close();

		std::cout << info << "\n\n";
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
	std::string Puzzle::LoadInput()
	{
		std::ifstream file(this->m_InputFilePath.data(), std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			std::cout << "[Puzzle Error] Failed to open " << this->m_InputFilePath << ".\n";
			return "";
		}
		size_t inputSize = file.tellg();
		file.seekg(0);
		std::string input(inputSize, 0);
		file.read(input.data(), inputSize);
		file.close();
		std::cout << "Calculating result for " << this->m_InputFilePath << ".\n";
		return input;
	}

}