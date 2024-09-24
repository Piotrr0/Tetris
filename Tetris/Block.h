#pragma once
#include "raylib.h";
#include <vector>
#include "Colors.h"


class Block
{

public:

    Block(Vector2 position, int size);
    virtual Block* Clone() const = 0;

    void Draw();
    void Move(Vector2 moveVector);
    void Rotate();

    Vector2 GetTileScreenPosition(Vector2 tile);

private:

    Vector2 originPosition = Vector2{ 0.f, 0.f };
    int currentRotation = 0;
    int tileSize = 0;
    int ID = 1;

protected:
    std::vector<std::vector<Vector2>> tiles;

public:

    inline Vector2 GetPosition() const { return originPosition; }
    inline std::vector<Vector2> GetCurrentTileSet() const { return tiles[currentRotation]; }
    inline int GetID() const { return ID; }
    inline int GetTileSize() const { return tileSize; }

    void SetPostion(Vector2 position) { originPosition = position; }

};