#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "raylib.h"


class Game;
class Skill;


class Actor
{
public:
    Actor();
    virtual ~Actor();

    virtual void Init(Game& gameRef, Vector2 playerPosition, std::string animation, int animNumber);
    virtual void Update(float dt);
    virtual void UpdatePosition(float dt);
    virtual void UpdateCollision(float dt);
    virtual void UpdateSkills(float dt);
    virtual void UpdateAnimation(float dt);
    virtual void DrawSkills(float dt);
    virtual void Draw(float dt);

    virtual void OnCollision(Actor& actor);

    void AddSkill(std::unique_ptr<Skill> skill);

    Vector2 GetPosition() const;
    Vector2 GetCenteredPosition() const;
    const Rectangle& GetCollider() const;
    uint32_t GetCollisionLayer() const;
    uint32_t GetCollisionMask() const;
    float GetHeight() const;
    float GetWidth() const;

    void TakeDamage(float damage);

    Game* GetGame() const;

    virtual void Dies();
    virtual bool IsAlive();
protected:
    Game* game = nullptr;

    Vector2 oldPosition;
    Vector2 position;
    Vector2 direction = { 0, 0 };
    std::vector<Texture2D> animations;

    Rectangle collider;
    uint32_t collisionLayer;
    uint32_t collisionMask;

    std::vector<std::unique_ptr<Skill>> skills;
    float life = 100;
    int speed = 150;
    int animationSpeed = 6;
    int animationNumber = 1;
    float animationstate = 0;
    int animationIndex = 0;

    float height = 0.f;
    float width = 0.f;
    bool isMoving = false;

    bool isAlive = true;
};
