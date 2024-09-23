#include "Grid.h"
#include <raylib.h>
#include "Colors.h"


Grid::Grid()
{
	cellGrid.resize(gridWidth, std::vector<Cell>(gridHeight));

	const float offset = 15;
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			const float posX = i * cellSize + offset;
			const float posY = j * cellSize + 5.f * offset;

			cellGrid[i][j].screenPosition = Vector2{ posX, posY };
			cellGrid[i][j].value = 0;
		}
	}
}

void Grid::DrawGrid()
{
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			Cell cell = cellGrid[i][j];
			const int gridValue = cell.value;
			const float posX = cell.screenPosition.x;
			const float posY = cell.screenPosition.y;
			DrawRectangle(posX, posY, cellSize - 1, cellSize - 1, Colors::GetColor(gridValue));
		}
	}
}
