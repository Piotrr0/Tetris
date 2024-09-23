#include "raylib.h"
#include "Tetris.h"
#include <functional>
#include <iostream>


Tetris::Tetris()
{
	InitializeWindow();
	Play();
}

void Tetris::Play()
{
	SpawnBlock();
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

	tetrisGrid->DrawGrid();
	DrawCurrentBlock();

	EndDrawing();
}

void Tetris::Tick()
{
	MoveDownTimer(moveDownTimer, moveDownTime);
	HandleMovements();
}

void Tetris::SpawnBlock()
{
	const std::vector<std::vector<Cell>> cellGrid = tetrisGrid->GetCellGrid();
	const int cellSize = tetrisGrid->GetCellSize();
	const float offset = (2 * cellSize); // shift block 2 cell up

	const Vector2 blockSpawnPosition = { cellGrid[4][0].screenPosition.x, cellGrid[4][0].screenPosition.y - offset };

	if (currentBlock)
	{
		currentBlock->position = blockSpawnPosition;
		currentBlock->size = cellSize;
		currentBlock->color = BLACK;
	}
}

void Tetris::DrawCurrentBlock()
{
	if (currentBlock)
	{
		DrawRectangle(currentBlock->position.x, currentBlock->position.y, currentBlock->size - 1, currentBlock->size - 1, currentBlock->color);
	}
}

void Tetris::HandleMovements()
{
	int keyPressed = GetKeyPressed();
	switch (keyPressed)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		break;
	}
}

void Tetris::MoveBlockDown()
{
	if (currentBlock)
	{
		const float cellSize = tetrisGrid->GetCellSize();
		currentBlock->position = Vector2{ currentBlock->position.x , currentBlock->position.y + cellSize };
	}
}

void Tetris::MoveBlockLeft()
{
	if (currentBlock)
	{
		const float cellSize = tetrisGrid->GetCellSize();
		currentBlock->position = Vector2{ currentBlock->position.x - cellSize , currentBlock->position.y};
	}
}

void Tetris::MoveBlockRight()
{
	if (currentBlock)
	{
		const float cellSize = tetrisGrid->GetCellSize();
		currentBlock->position = Vector2{ currentBlock->position.x + cellSize , currentBlock->position.y  };
	}
}

void Tetris::MoveDownTimer(float& timer, float duration)
{
	if (HandleCooldown(timer, duration))
	{
		MoveBlockDown();
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
