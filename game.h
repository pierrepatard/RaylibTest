#pragma once
#include <vector>

#include "input.h"
#include "define.h"
#include "actor.h"
#include "collisionSystem.h"
#include "mapGenerator.h"
#include "const.h"


class Game
{
public:
    void StartGame();

private:
    int screenWidth;
    int screenHeight;

    InputSystem input;
    Camera2D camera = { 0 };
    CollisionSystem collisionSystem;
    MapGenerator mapGenerator;

    std::vector< std::unique_ptr<Actor>>actors;
    bool consoleOpen;
};