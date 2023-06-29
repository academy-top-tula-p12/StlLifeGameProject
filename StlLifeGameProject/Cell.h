#pragma once
#include <vector>

enum class CellState
{
	Alife,
	Dead,
	Born
};

struct Position
{
	int row;
	int col;
};

std::vector<Position> Offset({ {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
							   {1, 0}, {1, -1}, {0, -1}, {-1, -1} });


class Cell
{
	Position position;
	CellState state;
	int neighbors;
public:
	Cell(int row, int col)
		: position{ row, col }, 
		state{ CellState::Alife }, 
		neighbors{} {}
	Cell(int row, int col, CellState state)
		: position{ row, col }, 
		state{ state }, 
		neighbors{} {}
	Cell(Position position, CellState state) :
		position{ position }, 
		state{ CellState::Alife }, 
		neighbors{} {}
	
	int Row() const	{ return position.row; }
	int Col() const { return position.col; }

	CellState& State() { return state; }
	int& Neightbors() { return neighbors; }

	friend bool operator==(Cell c1, Cell c2);
	friend bool operator!=(Cell c1, Cell c2);
};


bool operator==(Cell c1, Cell c2)
{
	return (c1.position.row == c2.position.row)
		&& (c1.position.col == c2.position.col);
}

bool operator!=(Cell c1, Cell c2)
{
	return !(c1 == c2);
}