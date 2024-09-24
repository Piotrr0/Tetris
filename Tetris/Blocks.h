#pragma once
#include "Block.h"
#include "raylib.h"
#include <vector>

class IBlock : public Block
{
public:
	IBlock(Vector2 position, int size) : Block(position, size)
	{
		tiles[0] = { Vector2{-1, 0}, Vector2{0, 0}, Vector2{1, 0}, Vector2{2, 0} };
		tiles[1] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1}, Vector2{0, 2} };
		tiles[2] = { Vector2{-1, 0}, Vector2{0, 0}, Vector2{1, 0}, Vector2{2, 0} };
		tiles[3] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1}, Vector2{0, 2} };
	}

	Block* Clone() const override 
	{
		return new IBlock(*this); 
	}
};

class JBlock : public Block
{
public:
	JBlock(Vector2 position, int size) : Block(position, size)
	{
		tiles[0] = { Vector2{-1, 0}, Vector2{0, 0}, Vector2{1, 0}, Vector2{1, 1} };
		tiles[1] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1}, Vector2{1, -1} };
		tiles[2] = { Vector2{-1, 0}, Vector2{0, 0}, Vector2{1, 0}, Vector2{-1, -1} };
		tiles[3] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1}, Vector2{-1, 1} };
	}

	Block* Clone() const override
	{
		return new JBlock(*this);
	}
};

class LBlock : public Block
{
public:
	LBlock(Vector2 position, int size) : Block(position, size)
	{
		tiles[0] = { Vector2{-1, 0}, Vector2{0, 0}, Vector2{1, 0}, Vector2{2, 0} };
		tiles[1] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1}, Vector2{0, 2} };
		tiles[2] = { Vector2{-1, 0}, Vector2{0, 0}, Vector2{1, 0}, Vector2{2, 0} };
		tiles[3] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1}, Vector2{0, 2} };
	}

	Block* Clone() const override
	{
		return new LBlock(*this);
	}
};

class OBlock : public Block
{
public:
	OBlock(Vector2 position, int size) : Block(position, size)
	{
		tiles[0] = { Vector2{0, 0}, Vector2{1, 0}, Vector2{0, 1}, Vector2{1, 1} };
		tiles[1] = { Vector2{0, 0}, Vector2{1, 0}, Vector2{0, 1}, Vector2{1, 1} };
		tiles[2] = { Vector2{0, 0}, Vector2{1, 0}, Vector2{0, 1}, Vector2{1, 1} };
		tiles[3] = { Vector2{0, 0}, Vector2{1, 0}, Vector2{0, 1}, Vector2{1, 1} };
	}

	Block* Clone() const override
	{
		return new OBlock(*this);
	}
};

class SBlock : public Block
{
public:
	SBlock(Vector2 position, int size) : Block(position, size)
	{
		tiles[0] = { Vector2{0, 0}, Vector2{1, 0}, Vector2{-1, 1}, Vector2{0, 1} };
		tiles[1] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{1, 0}, Vector2{1, 1} };
		tiles[2] = { Vector2{0, 0}, Vector2{1, 0}, Vector2{-1, 1}, Vector2{0, 1} };
		tiles[3] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{1, 0}, Vector2{1, 1} };
	}

	Block* Clone() const override
	{
		return new SBlock(*this);
	}
};

class TBlock : public Block
{
public:
	TBlock(Vector2 position, int size) : Block(position, size)
	{
		tiles[0] = { Vector2{-1, 0}, Vector2{0, 0}, Vector2{1, 0}, Vector2{0, 1} };
		tiles[1] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1}, Vector2{1, 0} };
		tiles[2] = { Vector2{-1, 0}, Vector2{0, 0}, Vector2{1, 0}, Vector2{0, -1} };
		tiles[3] = { Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1}, Vector2{-1, 0} };
	}

	Block* Clone() const override
	{
		return new TBlock(*this);
	}
};

