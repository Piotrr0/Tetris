#include "raylib.h"
#include "Tetris.h"
#include <iostream>
#include "Block.h"


Tetris::Tetris()
{
	InitializeWindow();
	Play();
}

void Tetris::Play()
{

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
	if (!currentBlock)
	{
		SpawnBlock();
	}

	MoveDownTimer(moveDownTimer, moveDownTime);
	HandleMovements();
}

void Tetris::SpawnBlock()
{
	const std::vector<std::vector<Cell>> cellGrid = tetrisGrid->GetCells();
	const int cellSize = tetrisGrid->GetCellSize();
	const float offset = (2.f * cellSize); // shift block 2 cell up

	const Vector2 blockSpawnPosition = { cellGrid[0][4].screenPosition.x, cellGrid[0][4].screenPosition.y - offset };

	if (!currentBlock)
	{
		currentBlock = new Block(blockSpawnPosition, cellSize, BLACK);
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
		const Vector2 moveVector = Vector2{ 0,-1 };
		currentBlock->Move(moveVector);

		if (!tetrisGrid->IsBlockInGrid(currentBlock))
		{
			const Vector2 moveVector = Vector2{ 0,1 };
			currentBlock->Move(moveVector);
			tetrisGrid->Place(currentBlock);

			delete currentBlock;
			currentBlock = nullptr;
		}
	}
}

void Tetris::MoveBlockLeft()
{
	if (currentBlock)
	{
		const Vector2 moveVector = Vector2{ -1, 0 };
		currentBlock->Move(moveVector);

		if (!tetrisGrid->IsBlockInGrid(currentBlock))
		{
			const Vector2 moveVector = Vector2{ 1,0 };
			currentBlock->Move(moveVector);
		}
	}
}

void Tetris::MoveBlockRight()
{
	if (currentBlock)
	{
		const Vector2 moveVector = Vector2{ 1,0 };
		currentBlock->Move(moveVector);
		if (!tetrisGrid->IsBlockInGrid(currentBlock))
		{
			const Vector2 moveVector = Vector2{ -1,0 };
			currentBlock->Move(moveVector);
		}
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
