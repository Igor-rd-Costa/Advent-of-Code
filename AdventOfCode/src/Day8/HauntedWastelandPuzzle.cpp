#include <iostream>
#include <thread>
#include <numeric>
#include "HauntedWastelandPuzzle.h"
#include "Timer.h"

namespace AoC2023 {

	HauntedWastelandPuzzle::HauntedWastelandPuzzle()
		: Puzzle("src/Day8/input", "src/Day8/info.txt")
	{

		m_Input = this->LoadInput();

		this->SolvePartOne(m_Input);
		this->SolvePartTwo(m_Input);
	}

	void HauntedWastelandPuzzle::SolvePartOne(const std::string& input)
	{
		AoC::Timer timer;
		size_t directionsEnd = input.find('\n');

		this->FindStart(directionsEnd);

		NodeIterator currentNode = m_Nodes.find("AAA");
		size_t count = 0;
		for (size_t i = 0; true; i++)
		{
			count++;
			char direction = input[i % directionsEnd];
			if (direction == 'L')
			{
				currentNode = this->FindLeft(&currentNode->second);
			}
			else
			{
				currentNode = this->FindRight(&currentNode->second);
			}

			if (currentNode->first == "ZZZ")
				break;
		}
		long long time = timer.GetTime();
		std::cout << "Part one: " << count << " in " << time << "ms.\n";
		m_Nodes.clear();

	}

	void HauntedWastelandPuzzle::SolvePartTwo(const std::string& input)
	{
		AoC::Timer timer;
		size_t directionsEnd = input.find('\n');

		this->ParseNodes(directionsEnd);

		std::vector<NodeIterator> starts;
		for (auto& node : m_Nodes)
		{
			if (node.first[2] == 'A')
			{
				starts.push_back(m_Nodes.find(node.first));
			}
		}
		std::vector<size_t> counts;
		counts.resize(starts.size());
		size_t count = 0;
		for (size_t i = 0; i < starts.size(); i++)
		{
			count = 0;
			for (size_t j = 0; true; j++)
			{
				count++;
				char direction = input[j % directionsEnd];
				if (direction == 'L')
				{
					starts[i] = this->FindLeft(&starts[i]->second);

					if (starts[i]->first[2] == 'Z')
					{
						counts[i] = count;
						break;
					}
				}
				else if (direction == 'R')
				{
					starts[i] = this->FindRight(&starts[i]->second);

					if (starts[i]->first[2] == 'Z')
					{
						counts[i] = count;
						break;
					}
				}
			}
		}

		size_t result = 1;
		for (size_t count : counts)
		{
			result = std::lcm<size_t>(result, count);
		}
		long long time = timer.GetTime();
		std::cout << "Part two: " << result << " in " << time << "ms.\n";
	}

	void HauntedWastelandPuzzle::FindStart(size_t offset)
	{
		m_Start = offset + 2;
		size_t end = m_Input.find("\n", m_Start);

		while (true)
		{
			std::string_view node(m_Input.c_str() + m_Start, 3);
			m_Nodes.insert({
				node,
				Node{
					this->GetLeft(),
					this->GetRight()
				}
			});


			m_Start = end + 1;
			end = m_Input.find('\n', m_Start);

			if (node == "AAA")
				break;
		}
	}

	void HauntedWastelandPuzzle::ParseNodes(size_t offset)
	{
		m_Start = offset + 2;
		size_t end = m_Input.find("\n", m_Start);

		while (end != m_Input.npos)
		{
			std::string_view node(m_Input.c_str() + m_Start, 3);
			m_Nodes.insert({
				node,
				Node{
					this->GetLeft(),
					this->GetRight()
				}
				});


			m_Start = end + 1;
			end = m_Input.find('\n', m_Start);
		}
	}

	NodeIterator HauntedWastelandPuzzle::FindLeft(Node* currentNode)
	{
		auto node = m_Nodes.find(currentNode->left);
		if (node != m_Nodes.end())
		{
			return node;
		}
		else
		{
			return this->FindNode(currentNode->left);
		}
	}

	NodeIterator HauntedWastelandPuzzle::FindRight(Node* currentNode)
	{
		auto node = m_Nodes.find(currentNode->right);
		if (node != m_Nodes.end())
		{
			return node;
		}
		else
		{
			return this->FindNode(currentNode->right);
		}
	}

	NodeIterator HauntedWastelandPuzzle::FindNode(std::string_view node)
	{
		size_t end = 0;
		while (end != m_Input.npos)
		{
			std::string_view newNode(m_Input.c_str() + m_Start, 3);
			auto result = m_Nodes.insert({
				newNode,
				Node{
				this->GetLeft(),
				this->GetRight()
				}
			});

			end = m_Input.find('\n', m_Start);
			m_Start = end + 1;
			
			if (newNode == node)
				return result.first;
		}

		return m_Nodes.end();
	}

	std::string_view HauntedWastelandPuzzle::GetLeft()
	{
		return std::string_view(m_Input.c_str() + m_Input.find('(', m_Start) + 1, 3);
	}

	std::string_view HauntedWastelandPuzzle::GetRight()
	{
		return std::string_view(m_Input.c_str() + m_Input.find('(', m_Start) + 6, 3);
	}



}