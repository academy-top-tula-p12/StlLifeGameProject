#pragma once
enum class CellType
{
	Empty,
	Life,
	Dead,
	Born
};

class Cell
{
	int row;
	int col;
	CellType state;
public:
	Cell(int row, int col)
		: row{ row }, col{ col }, state{ CellType::Life } {}
	
	int Row() const	{ return row; }
	int Col() const { return col; }

	CellType& State() { return state; }

	friend bool operator==(Cell c1, Cell c2);
	friend bool operator!=(Cell c1, Cell c2);
};

