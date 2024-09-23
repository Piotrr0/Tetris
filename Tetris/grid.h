#pragma once
#include <vector>
#include "raylib.h"
#include "Block.h"

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
	void Draw();
	bool IsBlockInGrid(Block* block);
	bool CheckCollision(Block* block);
	void Place(Block* block);
	bool IsInsideGrid(Vector2 position);
	bool IsInsideGridXY(Vector2 indecies);

private:

	Vector2 PositionToIndices(Vector2 position);
	bool IsCellEmpty(Vector2 position);
	bool IsCellEmptyXY(Vector2 indices);



private:

	const int cols = 10;
	const int rows = 20;
	const int cellSize = 30;
	const int offset = 15;
	std::vector<std::vector<Cell>> cells;
	std::vector<std::vector<Color>> colors;


public:

	inline std::vector<std::vector<Cell>> GetCells() const { return cells; }
	inline int GetCellSize() const { return cellSize; }

};

