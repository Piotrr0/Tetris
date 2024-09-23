#pragma once
#include <vector>
#include "raylib.h"

struct Cell
{
	Cell(int value, Vector2 screenPosition)
	{
		this->value = value;
		this->screenPosition = Vector2{ screenPosition };
	}
	Cell()
	{
		this->value = 0;
		this->screenPosition = Vector2{0.f,0.f};
	}

	int value;
	Vector2 screenPosition;
};

class Grid
{
public:
	Grid();
	void DrawGrid();
private:


private:

	int gridWidth = 10;
	int gridHeight = 20;
	int cellSize = 30;
	std::vector<std::vector<Cell>> cellGrid;
	std::vector<std::vector<Color>> colors;


public:

	inline std::vector<std::vector<Cell>> GetCellGrid() const { return cellGrid; }
	inline int GetCellSize() const { return cellSize; }

};

