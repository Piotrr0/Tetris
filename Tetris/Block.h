#pragma once
#include "raylib.h";
#include <vector>



class Block
{
public:

    Block(Vector2 position, int size, Color color);


    void Draw();
    void Move(Vector2 moveVector);
    Vector2 GetTileScreenPosition(Vector2 tile);


private:


private:

    Vector2 originPosition = Vector2{ 0.f, 0.f };
    std::vector<Vector2> tiles = { Vector2{0,0}, Vector2{0,1}, Vector2{1,0} };
    int tileSize = 0;
    Color color = BLACK;
    int blockID = 1;

public:

    inline Vector2 GetPosition() const { return originPosition; }
    inline std::vector<Vector2> GetTiles() const { return tiles; }
    inline int GetBlockID() const { return blockID; }

};