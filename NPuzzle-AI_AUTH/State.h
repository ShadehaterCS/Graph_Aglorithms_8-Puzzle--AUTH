#pragma once
#include <iostream>
#include <vector>
#include <string>
class State
{
struct coordinates { int x; int y; };

private:
public:
	std::string stringrepresentation;
	int* tiles;
	int size = 0;
	State* parent;
	coordinates emptyTile;

	State();
	State(int dimensions, int* numbers);
	State(const State&state);

	~State();

	std::vector<State> expand();
	std::string toString();

	bool isSolvable();

	//heuristic value
	int tilesOutOfPlace();

	//Operator overloads
	State& operator = (const State& state);
	bool operator < (const State& rhs);
	friend bool operator == (const State& lhs, const State& rhs);
	friend bool operator <(const State& lhs, const State& rhs);

	coordinates getEmptyTileCoordinates() { return emptyTile; }

	void showEmptyTilesCoordinates() {
		std::cout << std::to_string(emptyTile.x+1) + " ";
		std::cout << emptyTile.y +1<< std::endl;
	}

	//Functions to check 
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();

	void testMoves();



};

