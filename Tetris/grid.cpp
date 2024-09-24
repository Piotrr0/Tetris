#include "Grid.h"
#include <raylib.h>
#include "Colors.h"
#include "Block.h"
#include <iostream>


Grid::Grid()
{
    cells.resize(rows + freeRows, std::vector<Cell>(cols));

    for (int i = 0; i < rows + freeRows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const float posX = j * cellSize + offset;
            const float posY = i * cellSize + offset;

            cells[i][j].screenPosition = Vector2{ posX, posY };
            cells[i][j].value = 0;
        }
    }
}

void Grid::Draw()
{
    for (int i = freeRows; i < rows + freeRows; i++)
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

bool Grid::IsBlockInGrid(Block* block)
{
    const std::vector<Vector2> tiles = block->GetCurrentTileSet();
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
    const std::vector<Vector2> tiles = block->GetCurrentTileSet();
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
    const std::vector<Vector2> tiles = block->GetCurrentTileSet();
    for (auto tile : tiles)
    {
        const Vector2 tilePosition = block->GetTileScreenPosition(tile);
        const Vector2 indices = PositionToIndices(tilePosition);
        if (IsInsideGridXY(indices))
        {
            cells[indices.y][indices.x].value = block->GetID();
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
    std::cout << indices.y << "," << indices.x << std::endl;
    return (indices.y >= 0 && indices.y < rows + freeRows && indices.x >= 0 && indices.x < cols);
}

Vector2 Grid::PositionToIndices(Vector2 position)
{
    const float posX = ((position.y - offset) / cellSize);
    const float posY = ((position.x - offset) / cellSize);
    return Vector2{ posY, posX };
}

bool Grid::IsCellEmpty(Vector2 position)
{
    const Vector2 indices = PositionToIndices(position);
    return IsCellEmptyXY(indices);
}

bool Grid::IsCellEmptyXY(Vector2 indices)
{
    if (IsInsideGridXY(indices))
    {
        //std::cout << indices.y << " " << indices.x << std::endl;
        Cell& cell = cells[indices.y][indices.x];
        return cell.value == 0;
    }
    return false;
}
