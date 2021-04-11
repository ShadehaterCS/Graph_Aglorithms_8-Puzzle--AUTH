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
	coordinates emptyTile;
	std::string stringrepresentation;
	int* tiles;
	int size = 0;
	int heuristic = 0;
	int g;
	std::string move;

	State* parent = nullptr;
	State* goal = nullptr;
	

	State();
	State(int dimensions, int* numbers, State* goal);
	State(const State& state);
	~State();

	std::vector<State> expand();
	std::vector<State> getPath();
	std::string toString();

	//heuristic calculation
	int const tilesOutOfPlace();

	//Operator overloads
	State& operator = (const State& state);
	friend bool operator == (const State& lhs, const State& rhs);
	friend bool operator <(const State& lhs, const State& rhs);

	//Functions to check available moves
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
};
