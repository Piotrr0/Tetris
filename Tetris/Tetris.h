#pragma once
#include "raylib.h"
#include "grid.h"
#include "iostream"
#include "Block.h"

class Tetris
{
public:
	Tetris();
	void Play();

private:
	void InitializeWindow();
	void Draw();
	void Tick();
	void SpawnBlock();

#pragma region movementsFunctions
	void HandleMovements();
	void MoveBlock(Vector2 direction);
	void MoveBlockDown();
	void MoveBlockSide(bool left);

	void MoveBlockLeft();
	void MoveBlockRight();

#pragma endregion

	void PlaceBlock(Block* block);

	void MoveDownTimer(float& timer, float duration);
	bool HandleCooldown(float& timer, float duration);


private:

	const int targetFPS = 60.f;

	const int windowHeight = 800;
	const int windowWidth = 800;
	const std::string windowName = "Tetris";

	const float moveDownTime = 0.5f;
	float moveDownTimer = 0.1f;

	Grid* tetrisGrid = new Grid;
	Block* currentBlock = nullptr;

public:

};

