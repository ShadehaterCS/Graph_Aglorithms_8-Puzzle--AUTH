// NPuzzle-AI_AUTH.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <set>
#include <unordered_set>
#include "State.h"
#include "CustomStructures.h"
int iterations;

/*
* tbd description
*/
template <typename T>
int generalSearch
(State& initial, State& goal, T& frontier) {
	//initialize member variables
	iterations = 0;
	frontier.push(initial);
	std::set<std::string> closed;

	while (!frontier.empty()) {
		State possibleSolution = frontier.top();
		frontier.pop();

		//check if current state is the goal state
		if (possibleSolution == goal) {
			std::cout << possibleSolution.toString() << std::endl;
			auto v = possibleSolution.path();

			std::cout << initial.toString() << std::endl;
			std::cout << possibleSolution.toString() << std::endl;
			std::cout << iterations << std::endl;

			return iterations;
		}

		//if state not in the closed set then it's expanded
		if (closed.count(possibleSolution.stringrepresentation) == 0) {
			closed.insert(possibleSolution.stringrepresentation);
			std::vector<State> children = possibleSolution.expand();
			for (State state : children) {
				frontier.push(state);
			}
		}
		iterations++;
	}
	std::cout << "Solution not found" << std::endl;
	return -1;
}

int BestFS(State initial, State goal) {
	using namespace shd;
	PriorityQueue queue;
	return generalSearch(initial, goal, queue);
}

int BFS(State initial, State goal) {
	using namespace shd;
	Queue queue;
	return generalSearch(initial, goal, queue);
}
int DFS(State initial, State goal) {
	std::stack<State> frontier;
	return generalSearch(initial, goal, frontier);
}

int main() {
	int initNums[9] = { 3, 6, 0, 1, 4, 2, 7, 5, 8 };
	int goalNums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

	iterations = 0;
	State goal(3, goalNums, nullptr);
	State initial(3, initNums, &goal);

	std::cout << "Starting state:\n" + initial.toString() << std::endl;

	DFS(initial, goal);
	BFS(initial, goal);
	BestFS(initial, goal);

	//std::cout<<BFS(initial, goal);

	std::cin.get();
	return 0;
}