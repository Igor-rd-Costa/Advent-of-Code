#pragma once
#include <unordered_map>
#include "Puzzle.h"

namespace AoC2023 {

	struct Node
	{
		std::string_view left;
		std::string_view right;
	};

	using NodeIterator = std::unordered_map<std::string_view, Node>::iterator;
	class HauntedWastelandPuzzle : public AoC::Puzzle
	{
	public:
		HauntedWastelandPuzzle();
		~HauntedWastelandPuzzle() = default;

	private:
		virtual void SolvePartOne(const std::string& input) override;
		virtual void SolvePartTwo(const std::string& input) override;

		void FindStart(size_t offset);
		void ParseNodes(size_t offset);
		NodeIterator FindLeft(Node* currentNode);
		NodeIterator FindRight(Node* currentNode);
		NodeIterator FindNode(std::string_view node);
		std::string_view GetLeft();
		std::string_view GetRight();

		std::unordered_map<std::string_view, Node> m_Nodes;
		size_t m_Start = 0;
		std::string m_Input = "";
	};
}