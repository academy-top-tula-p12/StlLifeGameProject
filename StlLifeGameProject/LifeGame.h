#pragma once
#include <algorithm>
#include "Cell.h"
#include "Console.h"

using namespace std;

class LifeGame
{
    const int Rows{ 100 };
    const int Cols{ 100 };

	vector<Cell> colony;
	Console console;
public:
	LifeGame() {}
	bool SetColony()
	{
		int row{};
		int col{};
		console.SetPosition(row, col);

		Key key;
		bool isExit{ false };
        bool isQuit{ false };

		auto it = colony.begin();

        while (true)
        {

            if (_kbhit())
            {
                key = (Key)console.ReadKey();
                switch (key)
                {
                case Key::ArrowLeft:
                    if (col > 0) col--;
                    break;
                case Key::ArrowRight:
                    if (col < Cols) col++;
                    break;
                case Key::ArrowUp:
                    if (row > 0) row--;
                    break;
                case Key::ArrowDown:
                    if (row < Rows) row++;
                    break;
                case Key::Space:
                {
                    Cell candidat(row, col);
                    it = IsColony(candidat);
                    if (it == colony.end())
                        colony.push_back(candidat);
                    else
                        colony.erase(it);
                    ColonyShow();
                    break;
                }
                case Key::Esc:
                    isExit = true;
                    isQuit = true;
                    break;
                case Key::Enter:
                    // старт жизни
                    isExit = true;
                    break;
                }
            }
            if (isExit) break;
            console.SetPosition(row, col * 2);
        }

        return !isQuit;
	}

    void ColonyShow()
    {
        console.Clear();
        for (auto cell : colony)
            console.WritePosition(cell.Row(), cell.Col() * 2, string(2, (char)178));
    }

    vector<Cell>::iterator IsColony(Cell cell)
    {
        auto it = find_if(colony.begin(), colony.end(),
            [&cell](Cell item) { return cell == item; });
        return it;
    }

    bool IsColony(int row, int col)
    {
        Cell cell(row, col);
        auto it = find_if(colony.begin(), colony.end(),
            [&cell](Cell item) {
                return (cell == item && item.State() != CellState::Born);
            });
        return it != colony.end();
    }

    void Generate()
    {
        // count of neightbors
        for (auto cell = colony.begin(); cell != colony.end(); cell++)
        {
            cell->Neightbors() = 0;
            for (Position ncell : Offset)
                if (IsColony(cell->Row() + ncell.row, cell->Col() + ncell.col))
                    cell->Neightbors()++;
        }

        // dead alones and more
        for (auto cell = colony.begin(); cell != colony.end(); cell++)
        {
            if (cell->Neightbors() < 2 || cell->Neightbors() > 3)
                cell->State() = CellState::Dead;
        }

        // born cells
        for(int i = 0; i < colony.size(); i++)
        {
            for (Position off : Offset)
            {
                Cell candidat(colony[i].Row() + off.row, colony[i].Col() + off.col, CellState::Born);
                if (IsColony(candidat) == colony.end())
                {
                    for (Position coff : Offset)
                    {
                        Cell tmpCell(candidat.Row() + coff.row, candidat.Col() + coff.col);
                        auto it = IsColony(tmpCell);
                        if (it != colony.end() && it->State() != CellState::Born)
                            candidat.Neightbors()++;
                    }
                    if (candidat.Neightbors() == 3)
                        colony.push_back(candidat);
                }
            }
        }

        // earse dead, born to alive
        for (int i = 0; i < colony.size();)
        {
            if (colony[i].State() == CellState::Dead)
                colony.erase(colony.begin() + i);
            else
            {
                colony[i].State() = CellState::Alife;
                i++;
            }
            if (colony.size() == 0) break;
        }
    }

    void CursorOn() { console.CursorVisible(true); }
    void CursorOff() { console.CursorVisible(false); }
    
    void Wait()
    {
        _getch();
    }
};

