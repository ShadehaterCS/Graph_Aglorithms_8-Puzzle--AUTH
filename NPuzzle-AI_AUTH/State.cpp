#include "State.h"
#include <algorithm>

State::State() {
	tiles = nullptr;
	size = 0;
	parent = nullptr;
	emptyTile = { 0,0 };
	stringrepresentation = "";
}

State::State(int size, int* numbers, State* goal) {
	this->size = size;
	parent = nullptr;
	emptyTile = { 0,0 };
	tiles = new int[size * size];
	this->goal = goal;

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

	for (int i = 0; i < size * size; i++)
		tiles[i] = state.tiles[i];
}

State::~State() {
	delete[]tiles;
}

std::vector<State> State::expand() {
	std::vector<State> children;

	if (moveUp()) {
		//create a copy of the array
		int* newArray = new int[size * size];
		std::memcpy(newArray, tiles, sizeof(int) * size * size);

		//get the 2 positions to be swapped from the parent State's array
		int emptyPos = emptyTile.x + emptyTile.y * size;
		int emptyDestionation = emptyTile.x + (emptyTile.y - 1) * size;

		//swap the values
		newArray[emptyPos] = tiles[emptyDestionation];
		newArray[emptyDestionation] = 0;

		State child(size, newArray, goal);
		child.parent = new State(*this);

		children.push_back(child);
	}
	if (moveDown()) {
		int* newArray = new int[size * size];
		std::memcpy(newArray, tiles, sizeof(int) * size * size);

		int emptyPos = emptyTile.x + emptyTile.y * size;
		int emptyDestionation = emptyTile.x + (emptyTile.y + 1) * size;

		newArray[emptyPos] = tiles[emptyDestionation];
		newArray[emptyDestionation] = 0;
		State child(size, newArray, goal);
		child.parent = new State(*this);

		children.push_back(child);
	}
	if (moveLeft()) {
		int* newArray = new int[size * size];
		std::memcpy(newArray, tiles, sizeof(int) * size * size);

		int emptyPos = emptyTile.x + emptyTile.y * size;
		int emptyDestionation = (emptyTile.x - 1) + emptyTile.y * size;

		newArray[emptyPos] = tiles[emptyDestionation];
		newArray[emptyDestionation] = 0;
		State child(size, newArray, goal);
		child.parent = new State(*this);

		children.push_back(child);
	}
	if (moveRight()) {
		int* newArray = new int[size * size];
		std::memcpy(newArray, tiles, sizeof(int) * size * size);

		int emptyPos = emptyTile.x + emptyTile.y * size;
		int emptyDestionation = (emptyTile.x + 1) + emptyTile.y * size;

		newArray[emptyPos] = tiles[emptyDestionation];
		newArray[emptyDestionation] = 0;

		State child(size, newArray, goal);
		child.parent = new State(*this);

		children.push_back(child);
	}
	for (State state : children)
		if (state.parent == &state)
			std::cout << "Jesus fuck\n";
	return children;
}

std::vector<State> State::path()
{
	std::vector<State> path;
	State* temp = this;
	while (temp->parent != nullptr) {
		path.push_back(*temp);
		temp = temp->parent;
	}
	//std::reverse(path.begin(), path.end());
	return path;
}

std::string State::toString() {
	std::string ret;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			ret += std::to_string(tiles[x + y * size]) + " | ";
		}
		ret += "\n";
	}
	return ret;
}
//Operator overloads
State& State::operator=(const State& state) {
	size = state.size;
	parent = state.parent;
	emptyTile = state.emptyTile;
	tiles = new int[size * size];
	stringrepresentation = state.stringrepresentation;
	goal = state.goal;
	heuristic = tilesOutOfPlace();

	for (int i = 0; i < size * size; i++)
		tiles[i] = state.tiles[i];

	return *this;
}
bool operator==(const State& lhs, const State& rhs) {
	return lhs.stringrepresentation == rhs.stringrepresentation;
}

bool operator<(const State& lhs, const State& rhs) {
	return lhs.stringrepresentation < rhs.stringrepresentation;
}

//heuristic value function
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

bool State::moveUp()
{
	if (emptyTile.y - 1 >= 0)
		return true;
	return false;
}

bool State::moveDown()
{
	if (emptyTile.y + 1 < size)
		return true;
	return false;
}

bool State::moveLeft()
{
	if (emptyTile.x - 1 >= 0)
		return true;
	return false;
}

bool State::moveRight()
{
	if (emptyTile.x + 1 < size)
		return true;
	return false;
}