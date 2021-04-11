/* NPuzzle-AI_AUTH.cpp : This file contains the 'main' function. Program execution begins and ends there.
* @author Elias Kordoulas
* @subject AI - NPuzzle solver using Graph Traversal Algorithms
*/
#include <iostream>
#include <stack>
#include <set>
#include <chrono>
#include "State.h"
#include "CustomStructures.h"

/*
* Implements the general search algorithm
* The only difference between various algorithms is the implementation of the search's frontier
* so a @template is used. Specific overloads to comparators and functions in order to use the same names
* are handled in the "CustomStructures.h" file.
* The first state in the frontier is examined, if it's not the goal state then it's expanded and its children
* are added to the frontier.
*/
template <typename T>
std::pair<int, std::vector<State>> generalSearch(State& initial, State& goal, T& frontier) {
	auto startTime = std::chrono::high_resolution_clock::now();
	//initialize member variables
	int iterations = 0;
	frontier.push(initial);
	std::set<std::string> closed;

	while (!frontier.empty()) {
		State possibleSolution = frontier.top();
		frontier.pop();

		//check if current state is the goal state
		if (possibleSolution == goal) {
			//stop the clock
			auto endTime = std::chrono::high_resolution_clock::now();
			auto runningTimeMS = std::chrono::duration_cast
				<std::chrono::milliseconds>(endTime - startTime).count();
			//path vector, @returns States from start to end
			auto path = possibleSolution.getPath();

			std::pair<int, std::vector<State>> result(iterations, path);

			showResults(runningTimeMS, result);
			return result;
		}
		//if state not in the closed set then it's expanded and its children added to the frontier data structure
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
	std::pair<int, std::vector<State> >p1;
	return p1;
}


/*
* Uses simple queue, no comparators needed
*/
std::pair<int, std::vector<State>> BFS(State initial, State goal) {
	shd::Queue frontier;
	return generalSearch(initial, goal, frontier);
}
/*
* Uses simple stack, no comparators needed
*/
std::pair<int, std::vector<State>> DFS(State initial, State goal) {
	std::stack<State> frontier;
	return generalSearch(initial, goal, frontier);
}
/*
* Best First requires a heuristic to use the priority queue
* State objects provide it through int::heuristic member variable
*/
std::pair<int, std::vector<State>> BestFS(State initial, State goal) {
	shd::PriorityQueue frontier;
	return generalSearch(initial, goal, frontier);
}
/*
* A* requires a compoudnd heuristic to use the priority queue
* State objects provided it through int::heuristic and int::g member variables
* The compound heuristic is express as [h(State) + g(State)]
*/
std::pair<int, std::vector<State>> AStar(State initial, State goal) {
	shd::AStarPriorityQueue frontier;
	return generalSearch(initial, goal, frontier);
}

void showResults(long long time, std::pair<int, std::vector<State>> result) {
	using namespace std;
	cout << "Running time: " + to_string(time) + "ms" << endl;
	cout << "Possible solutions examined: " + to_string(result.first) << endl;
	cout << "Path length: " + to_string(result.second.size() - 1) << endl;
	string choice;
	cout << "Would you like to see the path? (Y/N): ";
	cin >> choice;
	if (choice == "Y" || choice == "y") {
		for (auto step : result.second)
			cout << step.toString() << endl;
		for (auto step : result.second)
			cout << step.move << endl;
	}
}

void CLI(State start, State goal) {
	using namespace std;
	cout << "Welcome to the N-Puzzle Solver" << endl;
	cout << "Default initial puzzle state is:\n" + start.toString() << endl;
	cout << "Default goal puzzle state is:\n" + goal.toString() << endl;

	int choice = 0;
	while (choice != -1) {
		cout << "Choose a searching algorithm:\n1.DFS\n2.BFS\n3.BestFS\n4.A*" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			DFS(start, goal);
			break;
		case 2:
			BFS(start, goal);
			break;
		case 3:
			BestFS(start, goal);
			break;
		case 4:
			AStar(start, goal);
			break;
		default:
			return;
		}
	}
}

int main() {
	int initNums[9] = { 3, 6, 0, 1, 4, 2, 7, 5, 8 };
	int goalNums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

	State goal(3, goalNums, nullptr);
	State initial(3, initNums, &goal);
	CLI(initial, goal);

	return 0;
}