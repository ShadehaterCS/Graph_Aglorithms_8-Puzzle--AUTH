// NPuzzle-AI_AUTH.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <set>
#include <chrono> 

#include "State.h"
#include "CustomStructures.h"

int iterations;

/*
* tbd description
*/
template <typename T>
std::pair<int, std::vector<State>> generalSearch (State& initial, State& goal, T& frontier) {
	auto startTime = std::chrono::high_resolution_clock::now();
	//initialize member variables
	iterations = 0;
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
	std::pair<int, std::vector<State> >p1;
	return p1;
}

std::pair<int, std::vector<State>> BestFS(State initial, State goal) {
	using namespace shd;
	PriorityQueue frontier;
	return generalSearch(initial, goal, frontier);
}

std::pair<int, std::vector<State>> BFS(State initial, State goal) {
	using namespace shd;
	Queue frontier;
	return generalSearch(initial, goal, frontier);
}
std::pair<int, std::vector<State>> DFS(State initial, State goal) {
	std::stack<State> frontier;
	return generalSearch(initial, goal, frontier);
}

std::pair<int, std::vector<State>> AStar(State initial, State goal) {
	shd::AStarPriorityQueue frontier;
	return generalSearch(initial, goal, frontier);
}

void showResults(long long time, std::pair<int, std::vector<State>> result){
	using namespace std;
	cout << "Running time: " + to_string(time) + "ms" << endl;
	cout << "Possible solutions examined: " + to_string(result.first) << endl;
	cout << "Path length: " + to_string(result.second.size()-1) << endl;
	string choice;
	cout << "Would you like to see the path? (Y/N): ";
	cin >> choice;
	if (choice == "Y" || choice == "y")
		for (auto step : result.second)
			cout << step.toString() << endl;

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
		}
	}
}

int main() {
	int initNums[9] = { 3, 6, 0, 1, 4, 2, 7, 5, 8 };
	int goalNums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

	iterations = 0;
	State goal(3, goalNums, nullptr);
	State initial(3, initNums, &goal);

	/*DFS(initial, goal);
	BFS(initial, goal);
	BestFS(initial, goal);
	AStar(initial, goal);*/

	CLI(initial, goal);
	return 0;
}