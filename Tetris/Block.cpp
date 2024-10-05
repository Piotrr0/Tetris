#include "Block.h"
#include <vector>
#include "raylib.h"
#include "Colors.h"

Block::Block(Vector2 position, int size) : originPosition(position), tileSize(size)
{
	tiles.resize(4, std::vector<Vector2>(4));
}

void Block::Draw()
{
	const std::vector<Vector2> currentTileSet = tiles[currentRotation];
	for (auto tile : currentTileSet)
	{
		const Vector2 tilePosition = GetTileScreenPosition(tile);
		const int posX = static_cast<int>(tilePosition.x);
		const int posY = static_cast<int>(tilePosition.y);

		DrawRectangle(posX, posY, tileSize - 1, tileSize - 1, Colors::GetColor(ID));
	}
}

void Block::Move(Vector2 moveVector)
{
	const float offsetRight = moveVector.x * tileSize;
	const float offsetUp = moveVector.y * tileSize;

	const Vector2 desiredPosition = Vector2{ originPosition.x + offsetRight, originPosition.y - offsetUp };
	originPosition = desiredPosition;
}

void Block::Rotate(bool left)
{
	if (left)
	{
		currentRotation = (currentRotation - 1 + 4) % 4;
	}
	else
	{
		currentRotation = (currentRotation + 1 + 4) % 4;
	}
}

Vector2 Block::GetTileScreenPosition(Vector2 tile)
{
	return Vector2{ originPosition.x + (tile.x * tileSize), originPosition.y + (tile.y * tileSize) };
}
