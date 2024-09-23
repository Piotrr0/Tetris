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
	void DrawCurrentBlock();

#pragma region movementsFunctions
	void HandleMovements();
	void MoveBlockDown();
	void MoveBlockLeft();
	void MoveBlockRight();

#pragma endregion


	void MoveDownTimer(float& timer, float duration);
	bool HandleCooldown(float& timer, float duration);


private:

	const float targetFPS = 60.f;

	const float windowHeight = 800.f;
	const float windowWidth = 800.f;
	std::string windowName = "Tetris";

	const float moveDownTime = 0.5f;
	float moveDownTimer = 0.1f;

	Grid* tetrisGrid = new Grid;
	Block* currentBlock = new Block;

public:

};

