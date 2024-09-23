#include "Block.h"
#include <vector>
#include "raylib.h"

Block::Block(Vector2 position, int size, Color color)
{
	this->originPosition = position;
	this->tileSize = size;
	this->color = color;
}

void Block::Draw()
{
	for (auto tile : tiles)
	{
		Vector2 tilePosition = GetTileScreenPosition(tile);
		DrawRectangle(tilePosition.x, tilePosition.y, tileSize - 1, tileSize - 1, color);
	}
}

void Block::Move(Vector2 moveVector)
{
	const float offsetRight = moveVector.x * tileSize;
	const float offsetUp = moveVector.y * tileSize;

	const Vector2 desiredPosition = Vector2{ originPosition.x + offsetRight, originPosition.y - offsetUp };
	originPosition = desiredPosition;
}

Vector2 Block::GetTileScreenPosition(Vector2 tile)
{	
	const Vector2 tilePosition = Vector2{ originPosition.x + (tile.x * tileSize), originPosition.y + (tile.y * tileSize) };
	return tilePosition;
}
