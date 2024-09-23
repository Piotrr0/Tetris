#include "Grid.h"
#include <raylib.h>
#include "Colors.h"
#include "Block.h"
#include <iostream>


Grid::Grid()
{
    cells.resize(rows, std::vector<Cell>(cols));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const float posX = j * cellSize + offset;
            const float posY = i * cellSize + (5.f * offset);

            cells[i][j].screenPosition = Vector2{ posX, posY };
            cells[i][j].value = 0;

        }
    }
}

void Grid::Draw()
{
    for (int i = 0; i < rows; i++)  
    {
        for (int j = 0; j < cols; j++) 
        {
            Cell& cell = cells[i][j];

            const int gridValue = cell.value;
            const float posX = cell.screenPosition.x;
            const float posY = cell.screenPosition.y;
            DrawRectangle(posX, posY, cellSize - 1, cellSize - 1, Colors::GetColor(gridValue));
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Grid::IsBlockInGrid(Block* block)
{
    const std::vector<Vector2> tiles = block->GetTiles();
    for (const auto& tile : tiles)
    {
        const Vector2 tilePosition = block->GetTileScreenPosition(tile);
        if (!IsInsideGrid(tilePosition))
        {
            return false;
        }
    }
    return true;
}

bool Grid::CheckCollision(Block* block)
{
    const std::vector<Vector2> tiles = block->GetTiles();
    for (auto tile : tiles)
    {
        const Vector2 tilePosition = block->GetTileScreenPosition(tile);
        if (!IsCellEmpty(tilePosition))
        {
            return true;
        }
    }
    return false;
}

void Grid::Place(Block* block)
{
    const std::vector<Vector2> tiles = block->GetTiles();
    for (auto tile : tiles)
    {
        const Vector2 tilePosition = block->GetTileScreenPosition(tile);
        const Vector2 indices = PositionToIndices(tilePosition);
        if (IsInsideGridXY(indices))
        {
            cells[indices.x][indices.y].value = block->GetBlockID();
        }
    }
}

bool Grid::IsInsideGrid(Vector2 position)
{
    const Vector2 indices = PositionToIndices(position);
    return IsInsideGridXY(indices);
}

bool Grid::IsInsideGridXY(Vector2 indices)
{
    if (indices.y < 0 || indices.y >= cols || indices.x >= rows)
    {
        return false;
    }
    return true;
}


Vector2 Grid::PositionToIndices(Vector2 position)
{
    const float posX = ((position.y - (5.f * offset)) / cellSize);
    const float posY = ((position.x - offset) / cellSize);
    return Vector2{ posX, posY };
}

bool Grid::IsCellEmpty(Vector2 position)
{
    const Vector2 indecies = PositionToIndices(position);
    return IsCellEmptyXY(indecies);
}

bool Grid::IsCellEmptyXY(Vector2 indices)
{
    if (IsInsideGridXY(indices))
    {
        Cell cell = cells[indices.x][indices.y];
        return cell.value == 0;
    }
    return false;
}
