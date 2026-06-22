#include "actor.h"
#include "utils.h"
#include <cassert>


Actor::~Actor()
{
    for (int i = 0; i < animationNumber; i++)
    {
        UnloadTexture(animations[i]);
    }
}


void Actor::Init(Vector2 playerPosition, std::string animation, int animNumber)
{
	position = playerPosition;
    
    animationNumber = animNumber;
    for (int i = 0; i < animationNumber; i++)
    {
        auto path = "sprites/" + animation + std::to_string(i + 1) + ".png";
        animations.push_back(LoadTexture(path.c_str()));
    }
    assert(!animations.empty(), "No annimation found for: %s", animation);

    width = animations[0].width;
    height = animations[0].height;

    collider = Rectangle{ position.x, position.y, width, height };
}


void Actor::Update(float dt)
{
    auto normalizedDirection = NormalizeV2(direction);
    auto velocity = normalizedDirection.x * normalizedDirection.x + normalizedDirection.y * normalizedDirection.y;

    if (velocity > 0.01)
    {
        isMoving = true;

        position.x += normalizedDirection.x * speed * dt;
        position.y += normalizedDirection.y * speed * dt;

        collider.x = position.x;
        collider.y = position.y;

        animationstate += animationSpeed * dt;
        animationIndex = (int)(animationstate) % animationNumber;
    }
    else
    {
        isMoving = false;
        animationstate = 0;
        animationIndex = 0;
    }
}


void Actor::Draw(float dt)
{
    DrawTextureV(animations[animationIndex], position, WHITE);
}


void Actor::OnCollision(Actor& actor)
{
}


const Vector2 Actor::GetPosition()
{
    return position;
}


const Rectangle& Actor::GetCollider()
{
    return collider;
}


const uint32_t Actor::GetCollisionLayer()
{
    return collisionLayer;
}


const uint32_t Actor::GetCollisionMask()
{
    return collisionMask;
}