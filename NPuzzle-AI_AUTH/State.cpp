#include "State.h"
#include <algorithm>

State::State() {}

State::State(int size, int* numbers, State* goal) {
	this->size = size;
	parent = nullptr;
	emptyTile = { 0,0 };
	tiles = new int[size * size];
	this->goal = goal;
	g = 0;
	heuristic = tilesOutOfPlace();

	//puzzles are always NxN size
	for (int i = 0; i < size * size; i++) {
		tiles[i] = numbers[i];
		if (numbers[i] == 0) {
			emptyTile.x = i % size;
			emptyTile.y = i / size;
		}
		stringrepresentation += std::to_string(tiles[i]);
	}
}

//Copy constructor
State::State(const State& state) {
	size = state.size;
	parent = state.parent;
	emptyTile = state.emptyTile;
	tiles = new int[size * size];
	stringrepresentation = state.stringrepresentation;
	goal = state.goal;
	heuristic = tilesOutOfPlace();
	g = state.g;
	move = state.move;
	std::memcpy(tiles, state.tiles, sizeof(int) * size * size);
}

State::~State() {
	delete[]tiles;
}

/*
* Expands the State aka creates new States from the original one
* The new states are dependant on the position of the empty tile.
* Depending on which directions the tile can move then a new State is created
* The lambda takes 2 @positional_args in order to swap the two numbers
* Parent assignment is done through a new copied object of the state that was expanded
*/
std::vector<State> State::expand() {
	std::vector<State> children;
	//lambda to reduce code reuse
	auto produceChild = [this](int pos1, int pos2, std::string move) {
		//create a new array that is a copy of this State. Swap the given positions and return a State object with the new array
		int* newArray = new int[size * size];
		std::memcpy(newArray, tiles, sizeof(int) * size * size);
		newArray[pos1] = tiles[pos2];
		newArray[pos2] = 0;

		State child(size, newArray, goal);
		child.parent = new State(*this);
		child.g = g + 1;
		child.move = move;
		delete[] newArray;
		return child;
	};

	if (moveUp()) {
		//get the 2 positions to be swapped from the parent State's array
		int emptyPos = emptyTile.x + emptyTile.y * size;
		int emptyDestination = emptyTile.x + (emptyTile.y - 1) * size;

		State child = produceChild(emptyPos, emptyDestination, "Go Up");
		children.push_back(child);
	}
	if (moveDown()) {
		int emptyPos = emptyTile.x + emptyTile.y * size;
		int emptyDestination = emptyTile.x + (emptyTile.y + 1) * size;

		State child = produceChild(emptyPos, emptyDestination, "Go Down");
		children.push_back(child);
	}
	if (moveLeft()) {
		int emptyPos = emptyTile.x + emptyTile.y * size;
		int emptyDestination = (emptyTile.x - 1) + emptyTile.y * size;

		State child = produceChild(emptyPos, emptyDestination, "Go Left");
		children.push_back(child);
	}
	if (moveRight()) {
		int emptyPos = emptyTile.x + emptyTile.y * size;
		int emptyDestination = (emptyTile.x + 1) + emptyTile.y * size;

		State child = produceChild(emptyPos, emptyDestination, "Go Right");
		children.push_back(child);
	}
	return children;
}
/*
* Goes upwards from the solution towards the starting state and
* @returns a reversed vector of the States that lead to the solution
*/
std::vector<State> State::getPath() {
	std::vector<State> path;
	State* temp = this;
	while (temp->parent != nullptr) {
		path.push_back(*temp);
		temp = temp->parent;
	}
	//for root node
	path.push_back(*temp);
	//reverse the vector in order for the path to be from start -> finish, rather than the other way around
	std::reverse(path.begin(), path.end());
	return path;
}
/*
* @returns a 'beauty' mode string representation of the internal array
* | x | x | x |
* | x | x | x |
* | x | x | x |
*/
std::string State::toString() {
	std::string ret;
	for (int y = 0; y < size; y++) {
		ret += "| ";
		for (int x = 0; x < size; x++) {
			ret += std::to_string(tiles[x + y * size]) + " | ";
		}
		ret += "\n";
	}
	return ret;
}
/*
* Assignment operator overload, essentially the same as the copy constructor
*/
State& State::operator=(const State& state) {
	size = state.size;
	parent = state.parent;
	emptyTile = state.emptyTile;
	tiles = new int[size * size];
	stringrepresentation = state.stringrepresentation;
	goal = state.goal;
	heuristic = tilesOutOfPlace();
	g = state.g;
	move = state.move;
	for (int i = 0; i < size * size; i++)
		tiles[i] = state.tiles[i];

	return *this;
}
bool operator==(const State& lhs, const State& rhs) {
	return lhs.stringrepresentation == rhs.stringrepresentation;
}
/*
* Simple heuristic function, returns the tiles that are out of place
* Most accurate measurement, since it directly shows at least how many moves must be made in order to reach the goal state
*/
int const State::tilesOutOfPlace() {
	if (goal == nullptr) 
		return 0;
	int outofplace = 0;
	for (unsigned int i = 0; i < stringrepresentation.length(); i++) {
		if (stringrepresentation.at(i) != goal->stringrepresentation.at(i))
			outofplace++;
	}
	return outofplace;
}

/**
 * @brief These functions provide the possible movements of the empty tiles
 *	which are easily calculated through the coordinates struct
 * @return true if a movement can be done
*/
bool State::moveUp() {
	if (emptyTile.y - 1 >= 0)
		return true;
	return false;
}

bool State::moveDown() {
	if (emptyTile.y + 1 < size)
		return true;
	return false;
}

bool State::moveLeft() {
	if (emptyTile.x - 1 >= 0)
		return true;
	return false;
}

bool State::moveRight() {
	if (emptyTile.x + 1 < size)
		return true;
	return false;
}