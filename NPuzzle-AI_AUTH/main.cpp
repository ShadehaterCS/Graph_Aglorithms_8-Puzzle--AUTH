// NPuzzle-AI_AUTH.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "State.h"
#include <stack>
#include <set>
#include <unordered_set>

int iterations;

template <typename T>
int generalSearch
	(State& initial, State& goal, T& frontier) {
	//initialize member variables
	iterations = 0;
	frontier.push(initial);
	std::set<State> closed;

	while (!frontier.empty()) {
		State possibleSolution = frontier.top();
		frontier.pop();

		if (possibleSolution == goal) {
			std::cout << possibleSolution.toString() << std::endl;
			return iterations;
		}

		if (closed.count(possibleSolution) == 0) {
			closed.insert(possibleSolution);

			std::vector<State> children = possibleSolution.expand();
			for (State state : children)
				frontier.push(state);
			std::cout << "Closed : "+ std::to_string(closed.size()) << std::endl;
			std::cout << "Frontier: "+ std::to_string(frontier.size()) << std::endl;
		}
		iterations++;
	}

	return -1;
}


int DFS(State initial, State goal) {
	std::stack<State> frontier;
	return generalSearch(initial, goal, frontier);
}

int main(){
	int initNums[9] = { 3, 6, 0, 1, 4, 2, 7, 5, 8 };
	int goalNums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

	iterations = 0;
	State initial(3, initNums);
	State goal(3, goalNums);


	std::cout << "Starting state:\n" + initial.toString() << std::endl;

	std::stack<State> stack;
	
	//generalSearch(initial, goal, stack);
	DFS(initial, goal);

	return 0;
}





