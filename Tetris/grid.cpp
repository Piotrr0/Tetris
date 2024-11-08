#include "Grid.h"
#include <raylib.h>
#include "Colors.h"
#include "Block.h"
#include <memory>
#include <iostream>

Grid::Grid()
{
    cells.resize(rows + freeRows, std::vector<Cell>(cols));

    for (int y = 0; y < rows + freeRows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            const float posX = static_cast<float>(x * cellSize + offset);
            const float posY = static_cast<float>(y * cellSize + offset);

            cells[y][x].screenPosition = Vector2{ posX, posY };
            cells[y][x].value = 0;
        }
    }
}

void Grid::Draw()
{
    for (int y = freeRows; y < rows + freeRows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            Cell& cell = cells[y][x];
            const int gridValue = cell.value;

            const int posX = static_cast<int>(cell.screenPosition.x);
            const int posY = static_cast<int>(cell.screenPosition.y);
            DrawRectangle(posX, posY, cellSize - 1, cellSize - 1, Colors::GetColor(gridValue));
        }
    }
}

bool Grid::IsBlockInGrid(std::shared_ptr<Block> block)
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

void Grid::Place(std::shared_ptr<Block> block)
{
    const std::vector<Vector2> tiles = block->GetCurrentTileSet();
    for (auto tile : tiles)
    {
        const Vector2 tilePosition = block->GetTileScreenPosition(tile);
        const Vector2 indices = PositionToIndices(tilePosition);
        if (IsInsideGridXY(indices))
        {
            int y = static_cast<int>(indices.y);
            int x = static_cast<int>(indices.x);
            cells[y][x].value = block->GetID();
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

bool Grid::CanBlockMove(std::shared_ptr<Block> block, Vector2 direction)
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
        int y = static_cast<int>(indices.y);
        int x = static_cast<int>(indices.x);
        return cells[y][x].value == 0;
    }
    return false;
}

void Grid::ClearFullRows()
{
    for (int y = rows + freeRows - 1; y >= 0; y--)
    {
        if (IsRowFull(y))
        {
            ClearRow(y);
            ShiftRowsDown(y);
            y++;
        }
    }
}

void Grid::ClearRow(int y)
{
    for (int x = 0; x < cols; x++)
    {
        cells[y][x].value = 0;
    }
}

void Grid::ShiftRowsDown(int fromRow)
{
    for (int y = fromRow; y > 0; y--)
    {
        for (int x = 0; x < cols; x++)
        {
            cells[y][x].value = cells[y - 1][x].value;
        }
    }

    for (int x = 0; x < cols; x++)
    {
        cells[0][x].value = 0;
    }
}

bool Grid::IsRowFull(int y)
{
    for (int x = 0; x < cols; x++)
    {
        if (cells[y][x].value == 0)
        {
            return false;
        }
    }
    return true;
}
