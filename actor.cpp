#include "actor.h"
#include "skill.h"
#include "game.h"

#include "utils.h"
#include "const.h"
#include "MapGenerator.h"
#include <cassert>


Actor::Actor() = default;


Actor::~Actor()
{
    for (int i = 0; i < animationNumber; i++)
    {
        UnloadTexture(animations[i]);
    }  
}

void Actor::Init(Game& gameRef, Vector2 playerPosition, std::string animation, int animNumber)
{
    game = &gameRef;
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


bool IsMapColliding(int x, int y, float width, int height)
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


Vector2 ResolveMapCollision(Vector2 start, Vector2 end, float width, float height, int steps = 8)
{
    {
        Vector2 result = start;

        auto resolveX = [&](float min, float max)
            {
                for (int i = 0; i < steps; ++i)
                {
                    float mid = (min + max) * 0.5f;

                    if (IsMapColliding(mid, result.y, width, height))
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

                    if (IsMapColliding(result.x, mid, width, height))
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

        if (IsMapColliding(result.x, result.y, width, height))
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
        if (IsMapColliding(position.x, position.y, width, height))
        {
            position = ResolveMapCollision(oldPosition, position, width, height);
            assert(!IsMapColliding(position.x, position.y, width, height));
            isMoving = GetDistanceV2(oldPosition, position) > 0.01f;

        }
    
        collider.x = position.x;
        collider.y = position.y;
    }
}


void Actor::UpdateSkills(float dt)
{
    for (auto& skill : skills)
    {
        skill->Update(dt);
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
    UpdateSkills(dt);
    UpdateAnimation(dt);
}


void Actor::AddSkill(std::unique_ptr<Skill> skill)
{
    skills.emplace_back(std::move(skill));
}



void Actor::DrawSkills(float dt)
{
    for (auto& skill : skills)
    {
        skill->Draw(dt);
    }
}


void Actor::Draw(float dt)
{
    DrawSkills(dt);
    DrawTextureV(animations[animationIndex], position, WHITE);
}


void Actor::OnCollision(Actor& actor)
{
}


Vector2 Actor::GetPosition() const
{
    return position;
}


Vector2 Actor::GetCenteredPosition() const
{
    return {
        position.x + width * 0.5f,
        position.y + height * 0.5f
    };
}


const Rectangle& Actor::GetCollider() const
{
    return collider;
}


uint32_t Actor::GetCollisionLayer() const
{
    return collisionLayer;
}


uint32_t Actor::GetCollisionMask() const
{
    return collisionMask;
}

Game* Actor::GetGame() const
{
    return game;
}


void Actor::Dies()
{
    isAlive = false;
}


bool Actor::IsAlive()
{
    return isAlive;
}


void Actor::TakeDamage(float damage)
{
    std::cout << ("Actor TakeDamage %f", damage) << std::endl;
    life -= damage;
    if (life <= 0)
    {
        Dies();
    }
}