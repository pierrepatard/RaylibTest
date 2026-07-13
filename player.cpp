#include "player.h"
#include "input.h"
#include "utils.h"
#include "enemy.h"

 
Player::Player()
{
    dash = LoadTexture("sprites/dash.png");
}


Player::~Player()
{
    UnloadTexture(dash);
}


void Player::RegisterPlayerBinding()
{
    if (auto forward = InputSystem::CreateKeyAction("MoveForward"))
    {
        forward->BindPressAction([this](float dt)
            {
                direction.y--;
            });
        forward->BindReleaseAction([this](float dt)
            {
                direction.y++;
            });
    }

    if (auto backward = InputSystem::CreateKeyAction("MoveBackward"))
    {
        backward->BindPressAction([this](float dt)
            {
                direction.y++;
            });
        backward->BindReleaseAction([this](float dt)
            {
                direction.y--;
            });
    }

    if (auto left = InputSystem::CreateKeyAction("MoveLeft"))
    {
        left->BindPressAction([this](float dt)
            {
                direction.x--;
            });
        left->BindReleaseAction([this](float dt)
            {
                direction.x++;
            });
    }

    if (auto right = InputSystem::CreateKeyAction("MoveRight"))
    {
        right->BindPressAction([this](float dt)
            {
                direction.x++;
            });
        right->BindReleaseAction([this](float dt)
            {
                direction.x--;
            });
    }

    if (auto right = InputSystem::CreateKeyAction("Dash"))
    {
        right->BindPressAction([this](float dt)
            {
                if (dashPhase == 0)
                {
                    dashPhase = 0.1;
                }
            });
    }
}


void Player::Init(Game& gameRef, Vector2 playerPosition)
{
    Actor::Init(gameRef, playerPosition, "front", 3);
    RegisterPlayerBinding();
    speed = 200;
    collisionLayer = static_cast<uint32_t>(ColliderLayer::PLAYER);
    collisionMask = static_cast<uint32_t>(ColliderLayer::ENEMY) | static_cast<uint32_t>(ColliderLayer::MAP);
}


void Player::Update(float dt)
{
    Actor::UpdatePosition(dt);
    if (dashPhase > 0)
    {
        if (dashPhase > 0.15 && dashPhase < 2)
        {
            if (isMoving)
            {
                auto normalizedDirection = NormalizeV2(direction);
                position.x += normalizedDirection.x * dashLengh;
                position.y += normalizedDirection.y * dashLengh;
            }
            dashPhase = 2;
        }
        dashPhase = (dashPhase > 2.1) ? 0 : dashPhase + dt;
    }
    UpdateCollision(dt);
    UpdateSkills(dt);
    UpdateAnimation(dt);
}


void Player::Draw(float dt)
{
    DrawSkills(dt);
    if (dashPhase > 0)
    {
        Vector2 tempPosition = position;
        tempPosition.y += quaterSize;
        DrawTextureV(dash, tempPosition, WHITE);
    }
    else
    {
        DrawTextureV(animations[animationIndex], position, WHITE);
    }
}


void Player::OnCollision(Actor& actor)
{
    switch (static_cast<ColliderLayer>(actor.GetCollisionLayer()))
    {
    case ColliderLayer::MAP:
        position = oldPosition;
        collider.x = position.x;
        collider.y = position.y;
        break;
    }
}


void Player::Dies()
{
    Print("Player is dead !!");
}
