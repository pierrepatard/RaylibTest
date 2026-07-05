#include "actor.h"
#include "utils.h"
#include "const.h"
#include "MapGenerator.h"
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


bool IsColliding(int x, int y, float width, int height)
{
    int leftTile = x / TILE_PIXEL;
    int rightTile = (x + width) / TILE_PIXEL;
    int topTile = y / TILE_PIXEL;
    int bottomTile = (y + height) / TILE_PIXEL;

    for (int y = topTile; y <= bottomTile; y++)
    {
        for (int x = leftTile; x <= rightTile; x++)
        {
            if (MapGenerator::GetTile(x, y) != TileType::FLOOR)
            {
                return true;
            }
        }
    }
    return false;
}


Vector2 ResolveCollision(Vector2 start, Vector2 end, float width, float height, int steps = 8)
{
    {
        Vector2 result = start;

        auto resolveX = [&](float min, float max)
            {
                for (int i = 0; i < steps; ++i)
                {
                    float mid = (min + max) * 0.5f;

                    if (IsColliding(mid, result.y, width, height))
                        max = mid;
                    else
                        min = mid;
                }

                result.x = min;
            };

        auto resolveY = [&](float min, float max)
            {
                for (int i = 0; i < steps; ++i)
                {
                    float mid = (min + max) * 0.5f;

                    if (IsColliding(result.x, mid, width, height))
                        max = mid;
                    else
                        min = mid;
                }

                result.y = min;
            };

        if (fabsf(end.x - start.x) > fabsf(end.y - start.y))
        {
            resolveX(start.x, end.x);
            resolveY(start.y, end.y);
        }
        else
        {
            resolveY(start.y, end.y);
            resolveX(start.x, end.x);
        }

        if (IsColliding(result.x, result.y, width, height))
        {
            return start;
        }
        return result;
    }
}


void Actor::UpdatePosition(float dt)
{
    oldPosition = position;
    auto normalizedDirection = NormalizeV2(direction);
    auto velocity = normalizedDirection.x * normalizedDirection.x + normalizedDirection.y * normalizedDirection.y;

    if (velocity > 0.01)
    {
        position.x += normalizedDirection.x * speed * dt;
        position.y += normalizedDirection.y * speed * dt;

        isMoving = true;
    }
    else
    {
        isMoving = false;
    }
}



void Actor::UpdateCollision(float dt)
{
    if (isMoving)
    {
        if (IsColliding(position.x, position.y, width, height))
        {
            position = ResolveCollision(oldPosition, position, width, height);
            assert(!IsColliding(position.x, position.y, width, height));
            isMoving = GetDistanceV2(oldPosition, position) > 0.01f;

        }
    
        collider.x = position.x;
        collider.y = position.y;
    }
}


void Actor::UpdateAnimation(float dt)
{
    if (isMoving)
    {
        animationstate += animationSpeed * dt;
        animationIndex = (int)(animationstate) % animationNumber;
    }
    else
    {
        animationstate = 0;
        animationIndex = 0;
    }

}

void Actor::Update(float dt)
{
    UpdatePosition(dt);
    UpdateCollision(dt);
    UpdateAnimation(dt);
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