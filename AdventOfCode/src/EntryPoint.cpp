#include <iostream>
#include "Puzzle.h"

int main() {
	// TODO move most of this out of the main function after I catch up on the puzzles :^) 
	char inputBuffer[50] = {};
	std::string buffer;
	bool isRunning = true;
	while (isRunning) {
		std::cout << "Advent of Code Puzzles:\n";
		AoC::Puzzle::ListPuzzles();
		std::cout << "\nType number of the puzzle you wish to load. /help for help.\n";
		std::cin >> buffer;
		if (buffer[0] == '/') {
			if (buffer == "/help") {
				std::cout << "/help - Shows this.\n/exit - Closes the program.";
			}
			else if (buffer == "/exit")
			{
				isRunning = false;
				break;
			}
			else
			{
				std::cout << "Invalid command. /help for a list of commmands.\n";
			}
		}
		else
		{
			AoC::Puzzle* puzzle = nullptr;
			int puzzleNumber = 0;
			try 
			{
				puzzleNumber = std::stoi(buffer);
				puzzle = AoC::Puzzle::Load(puzzleNumber);
				delete puzzle;
			}
			catch (std::invalid_argument e)
			{
				std::cout << "Invalid command.\n";
			}
			std::cout << "\n";
		}
	}
}