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
            const float posX = static_cast<float>(j * cellSize + offset);
            const float posY = static_cast<float>(i * cellSize + offset);

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

            const int posX = static_cast<int>(cell.screenPosition.x);
            const int posY = static_cast<int>(cell.screenPosition.y);
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

void Grid::Place(Block* block)
{
    const std::vector<Vector2> tiles = block->GetCurrentTileSet();
    for (auto tile : tiles)
    {
        const Vector2 tilePosition = block->GetTileScreenPosition(tile);
        const Vector2 indices = PositionToIndices(tilePosition);
        if (IsInsideGridXY(indices))
        {
            int row = static_cast<int>(indices.y);
            int col = static_cast<int>(indices.x);
            cells[row][col].value = block->GetID();
        }
    }

    ClearFullRows();
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

bool Grid::CanBlockMove(Block* block, Vector2 direction)
{
    const std::vector<Vector2> tiles = block->GetCurrentTileSet();
    for (auto tile : tiles)
    {
        const Vector2 currentPos = block->GetTileScreenPosition(tile);
        const Vector2 currentIndices = PositionToIndices(currentPos);
        const Vector2 newIndices = { currentIndices.x + direction.x, currentIndices.y - direction.y };

        if (!IsInsideGridXY(newIndices) || !IsCellEmptyXY(newIndices))
        {
            return false;
        }
    }
    return true;
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
        int row = static_cast<int>(indices.y);
        int col = static_cast<int>(indices.x);
        return cells[row][col].value == 0;
    }
    return false;
}

void Grid::ClearFullRows()
{
    for (int row = rows + freeRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            ShiftRowsDown(row);
            row++;
        }
    }
}

void Grid::ClearRow(int row)
{
    for (int col = 0; col < cols; col++)
    {
        cells[row][col].value = 0;
    }
}

void Grid::ShiftRowsDown(int fromRow)
{
    for (int row = fromRow; row > 0; row--)
    {
        for (int col = 0; col < cols; col++)
        {
            cells[row][col].value = cells[row - 1][col].value;
        }
    }

    for (int col = 0; col < cols; col++)
    {
        cells[0][col].value = 0;
    }
}

bool Grid::IsRowFull(int row)
{
    for (int col = 0; col < cols; col++)
    {
        if (cells[row][col].value == 0)
        {
            return false;
        }
    }
    return true;
}