#pragma once
#include <iostream>
#include <vector>
#include <string>
class State
{
	//Used to store the empty tile's position in the array 
	struct coordinates { int x; int y; };

private:
public:
	std::string stringrepresentation;
	int* tiles;
	int size = 0;
	int heuristic = 0;
	int g;

	std::string move;
	State* parent;
	State* goal;
	coordinates emptyTile;

	State();
	State(int dimensions, int* numbers, State* goal);
	State(const State& state);
	~State();

	std::vector<State> expand();
	std::vector<State> getPath();
	std::string toString();

	bool isSolvable();

	//heuristic calculation
	int const tilesOutOfPlace();

	//Operator overloads
	State& operator = (const State& state);
	bool operator < (const State& rhs);
	friend bool operator == (const State& lhs, const State& rhs);
	friend bool operator <(const State& lhs, const State& rhs);
	friend bool operator > (const State& lhs, const State& rhs) {
		return lhs.heuristic < rhs.heuristic;
	}

	coordinates getEmptyTileCoordinates() { return emptyTile; }

	void showEmptyTilesCoordinates() {
		std::cout << std::to_string(emptyTile.x + 1) + " ";
		std::cout << emptyTile.y + 1 << std::endl;
	}

	//Functions to check
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
};
