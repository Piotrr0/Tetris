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
	void InitializeBlocks();
	Vector2 CalculateSpawnPosition();
	Block* PickRandomBlock();
	void SpawnBlock(Block* blockToSpaw);

#pragma region movementsFunctions
	void HandleMovements();
	void MoveBlock(Vector2 direction);
	void SnapToBottom();
	void RotateBlock();

#pragma endregion

	void PlaceBlock(Block* block);

	void MoveDownTimer(float& timer, float duration);
	bool HandleCooldown(float& timer, float duration);


private:

	const int targetFPS = 60;

	const int windowHeight = 800;
	const int windowWidth = 800;
	const std::string windowName = "Tetris";

	const float moveDownTime = 0.5f;
	float moveDownTimer = 0.1f;

	Grid* tetrisGrid = new Grid;
	Block* currentBlock = nullptr;
	std::vector<Block*> blocks{};

public:

};

