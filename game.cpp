#pragma once
#include "actor.h"
#include "game.h"

#include "skill.h"
#include "beam.h"
#include "player.h"
#include "enemy.h"

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "keyAction.h"
#include "input.h"
#include "utils.h"
#include "command.h"
#include "mapGenerator.h"

#include <iostream>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <cmath>
#include <string>
#include <random>


Game::~Game() = default;


void Game::StartGame()
{
    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, "raylib test");
    //SetTargetFPS(60);  

#ifdef DEBUG
    consoleOpen = false;
    CommandSystem::RegisterCommands();
#endif

    input.LoadInputContext();

    mapGenerator = MapGenerator();
    mapGenerator.GenerateMap(MapType::CAVE);

    auto player = std::make_unique<Player>();
    player->Init(*this, { MAP_CENTER_WIDTH * TILE_PIXEL, MAP_CENTER_HEIGHT * TILE_PIXEL });
    player->AddSkill(std::make_unique<Beam>(*player));
    Player* playerRef = player.get();

    auto enemy1 = std::make_unique<Enemy>();
    enemy1->Init(*this, { (MAP_CENTER_WIDTH + 5) * TILE_PIXEL, MAP_CENTER_HEIGHT * TILE_PIXEL }, *player);

    auto enemy2 = std::make_unique<Enemy>();
    enemy2->Init(*this, { (MAP_CENTER_WIDTH - 5) * TILE_PIXEL, MAP_CENTER_HEIGHT * TILE_PIXEL }, *player);

    actors.push_back(std::move(player));
    actors.push_back(std::move(enemy1));
    actors.push_back(std::move(enemy2));

    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    auto cameraDeadZone = 30;
    auto cameraLerpStrenth = 5.0f;

#ifdef DEBUG
    if (auto toggleConsole = InputSystem::CreateKeyAction("ToggleConsole"))
    {
        toggleConsole->BindReleaseAction([this](float dt)
            {
                consoleOpen = !consoleOpen;
                if (consoleOpen)
                {
                    InputSystem::ClearStringBuffer();
                    input.SetCurrentContext(Context::CONSOLE);
                }
                else
                {
                    input.RestoreContext();
                }
            });
    }

    if (auto executeCommand = InputSystem::CreateKeyAction("ExecuteCommand"))
    {
        executeCommand->BindReleaseAction([this](float dt)
            {
                auto command = InputSystem::GetStringBuffer();
                CommandSystem::ExecuteCommand(command);
                InputSystem::ClearStringBuffer();
            });
    }

    if (auto popChar = InputSystem::CreateKeyAction("PopInputChar"))
    {
        popChar->BindReleaseAction([this](float dt)
            {
                InputSystem::PopStringBuffer();
            });
    }
  
#endif
 
    // -- Main game loop --
    while (!WindowShouldClose())
    {
        auto dt = GetFrameTime();

        // -- Update --
        input.CheckInputs(dt);

        for (auto& actor : actors)
        {
            actor->Update(dt);
        }

        std::erase_if(actors, [](const std::unique_ptr<Actor>& actor)
        {
            return !actor->IsAlive();
        });

        collisionSystem.CheckCollisions(actors);

        // -- Draw --
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);

        mapGenerator.DrawMap(camera);

        for (auto& actor : actors)
        {
            actor->Draw(dt);
        }

        EndMode2D();

        DrawRectangle(10, 5, 60, 20, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 5, 60, 20, BLUE);
        DrawText(TextFormat("FPS: %i", GetFPS()), 15, 11, 10, BLACK);

#ifdef DEBUG
        if (consoleOpen)
        {
            DrawRectangle(80, 0, GetScreenWidth(), 30, Fade(DARKGRAY, 0.9f));
            auto commandString = InputSystem::GetStringBuffer();
            DrawText(("> " + commandString).c_str(), 95, 5, 20, RAYWHITE);
        }
#endif

        Vector2 playerPos = playerRef->GetPosition();

        if (GetDistanceV2(camera.target, playerPos) > cameraDeadZone)
        {
            camera.target = Vector2Lerp(camera.target, playerPos, cameraLerpStrenth * dt );
        }
            

        EndDrawing();
    }
    CloseWindow();
}


const std::vector<std::unique_ptr<Actor>>& Game::GetActors() const
{
    return actors;
}
