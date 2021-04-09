#pragma once
#include <queue>
#include "State.h"

namespace shd {
	class Queue : public std::queue<State> {
	public:
		State top() {
			return front();
		}
	};
	
	/*
	* Custom comparator for State objects
	* Using > because a higher heuristic value means that solution is worse
	*
	*/
	struct StateComparator {
		bool operator()(State& lhs, State& rhs) {
			return lhs.heuristic > rhs.heuristic;
		}
	};
	/*
	* Created for easier use in other parts of the code
	*/
	class PriorityQueue : public std::priority_queue<State, std::vector<State>, StateComparator> {};
	
	//Use for A* algorithm
	struct AStar_StateComparator {
		bool operator()(State& lhs, State& rhs) {
			return (lhs.g + lhs.heuristic) > (rhs.g + rhs.heuristic);
		}
	};

	class AStarPriorityQueue : public std::priority_queue<State, std::vector<State>, AStar_StateComparator> {};

}