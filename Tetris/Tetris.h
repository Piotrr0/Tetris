#pragma once
#include "raylib.h"
#include "grid.h"
#include <iostream>
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
	std::shared_ptr<Block> PickRandomBlock();
	void SpawnBlock(std::shared_ptr<Block> blockToSpawn);

#pragma region movementsFunctions
	void HandleMovements();
	void MoveBlock(Vector2 direction);
	void SnapToBottom();
	void RotateBlock();

#pragma endregion

	void PlaceBlock();

	void MoveDownTimer(float& timer, float duration);
	bool HandleCooldown(float& timer, float duration);


private:

	const int targetFPS = 60;

	const int windowHeight = 800;
	const int windowWidth = 800;
	const std::string windowName = "Tetris";

	const float moveDownTime = 0.5f;
	float moveDownTimer = 0.1f;

	std::unique_ptr<Grid> tetrisGrid = std::make_unique<Grid>();
	std::shared_ptr<Block> currentBlock = nullptr; 
	std::vector<std::shared_ptr<Block>> blocks;

public:

};

