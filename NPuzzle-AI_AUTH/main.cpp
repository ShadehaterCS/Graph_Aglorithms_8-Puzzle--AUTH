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
	std::set<State> closed;

	while (!frontier.empty()) {
		//
		auto possibleSolution = frontier.top();
		frontier.pop();
		
		//check if current state is the goal state
		if (possibleSolution == goal) {
			std::cout << possibleSolution.toString() << std::endl;
			auto v = possibleSolution.path();
			for (auto s : v) {
				std::cout << s.toString() << std::endl;
			}
			std::cout << initial.toString() << std::endl;
			return iterations;
		}

		//if state not in the closed set then it's expanded
		if (closed.count(possibleSolution) == 0) {
				closed.insert(possibleSolution);

			std::vector<State> children = possibleSolution.expand();
			for (State state : children) {
				frontier.push(state);
			}
		}

		iterations++;
	}

	return -1;
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

int main(){
	int initNums[9] = { 3, 6, 0, 1, 4, 2, 7, 5, 8 };
	int goalNums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

	iterations = 0;
	State initial(3, initNums);
	State goal(3, goalNums);


	std::cout << "Starting state:\n" + initial.toString() << std::endl;
	
	DFS(initial, goal);


	//std::cout<<BFS(initial, goal);

	std::cin.get();
	return 0;
}





