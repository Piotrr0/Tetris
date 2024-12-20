﻿#include "raylib.h"
#include "Tetris.h"
#include "Blocks.h"
#include <memory>
#include <random>

Tetris::Tetris()
{
	InitializeWindow();
	InitializeBlocks();
	Play();
}

void Tetris::Play()
{
	std::shared_ptr<Block> randomBlock = PickRandomBlock();
	SpawnBlock(randomBlock);

	while (!WindowShouldClose())
	{
		Tick();
		Draw();
	}
	CloseWindow();
}

void Tetris::InitializeWindow()
{
	InitWindow(windowWidth, windowHeight, windowName.c_str());
	SetTargetFPS(targetFPS);

}

void Tetris::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	if (tetrisGrid)
	{
		tetrisGrid->Draw();
	}

	if (currentBlock)
	{
		currentBlock->Draw();
	}

	EndDrawing();
}

void Tetris::Tick()
{
	MoveDownTimer(moveDownTimer, moveDownTime);
	HandleMovements();
}

void Tetris::InitializeBlocks()
{
	const Vector2 defaultPosition = CalculateSpawnPosition();
	const int cellSize = tetrisGrid->GetCellSize();

	const int blocksCount = 6;
	blocks.reserve(blocksCount);

	blocks.push_back(std::make_shared<IBlock>(defaultPosition, cellSize));
	blocks.push_back(std::make_shared<JBlock>(defaultPosition, cellSize));
	blocks.push_back(std::make_shared<LBlock>(defaultPosition, cellSize));
	blocks.push_back(std::make_shared<OBlock>(defaultPosition, cellSize));
	blocks.push_back(std::make_shared<SBlock>(defaultPosition, cellSize));
	blocks.push_back(std::make_shared<TBlock>(defaultPosition, cellSize));
}

Vector2 Tetris::CalculateSpawnPosition()
{
	const std::vector<std::vector<Cell>> cellGrid = tetrisGrid->GetCells();
	const float offset = 2.f * tetrisGrid->GetCellSize();

	return { cellGrid[4][4].screenPosition.x, cellGrid[4][4].screenPosition.y - offset };
}

std::shared_ptr<Block> Tetris::PickRandomBlock()
{
	const int blocksCount = blocks.size() - 1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, blocksCount);

	int randomBlockIndex = dis(gen);
	std::cout << randomBlockIndex << std::endl;

	return blocks[randomBlockIndex];
}

void Tetris::SpawnBlock(std::shared_ptr<Block> blockToSpawn)
{
	if (blockToSpawn)
	{
		currentBlock = blockToSpawn;
	}
}

void Tetris::HandleMovements()
{
	int keyPressed = GetKeyPressed();
	switch (keyPressed)
	{
	case KEY_LEFT:
		MoveBlock(Vector2{ -1,0 });
		break;
	case KEY_RIGHT:
		MoveBlock(Vector2{ 1, 0 });
		break;
	case KEY_DOWN:
		MoveBlock(Vector2{ 0, -1 });
		break;
	case KEY_UP:
		RotateBlock();
		break;
	case KEY_SPACE:
		SnapToBottom();
		break;
	}
}

void Tetris::MoveBlock(Vector2 direction)
{
	if (currentBlock)
	{
		if (tetrisGrid->CanBlockMove(currentBlock, direction))
		{
			currentBlock->Move(direction);
		}
		else
		{
			if (direction.y > 0)
			{
				PlaceBlock();
			}
		}
	}
}

void Tetris::SnapToBottom()
{
	if (currentBlock)
	{
		const Vector2 moveVector = Vector2{ 0, -1 };
		while (tetrisGrid->CanBlockMove(currentBlock, moveVector))
		{
			currentBlock->Move(moveVector);
		}

		PlaceBlock();
	}
}

void Tetris::RotateBlock()
{
	if (currentBlock)
	{
		currentBlock->Rotate(true);
		if (!tetrisGrid->IsBlockInGrid(currentBlock))
		{
			currentBlock->Rotate(false);
		}
	}
}

void Tetris::PlaceBlock()
{
	if (currentBlock)
	{
		tetrisGrid->Place(currentBlock);
		currentBlock->SetPostion(CalculateSpawnPosition());

		std::shared_ptr<Block> randomBlock = PickRandomBlock();
		SpawnBlock(randomBlock);
	}
}

void Tetris::MoveDownTimer(float& timer, float duration)
{
	if (HandleCooldown(timer, duration))
	{
		MoveBlock(Vector2{ 0,-1 });
	}
}

bool Tetris::HandleCooldown(float& timer, float duration)
{
	timer -= GetFrameTime();
	if (timer <= 0)
	{
		timer = duration;
		return true;
	}
	return false;
}
