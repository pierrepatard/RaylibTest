#pragma once
#include <vector>
#include <memory>

#include "input.h"
#include "define.h"
#include "collisionSystem.h"
#include "mapGenerator.h"
#include "const.h"

class Actor;

class Game
{
public:
    ~Game();
    void StartGame();
    const std::vector<std::unique_ptr<Actor>>& GetActors() const;
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