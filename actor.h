#pragma once
#include "raylib.h"
#include <math.h>
#include <string>
#include <vector>

class Actor
{
public:
    virtual ~Actor();

    virtual void Init(Vector2 playerPosition, std::string animation, int animationNumber );
    virtual void Update(float dt);
    virtual void UpdatePosition(float dt);
    virtual void UpdateCollision(float dt);
    virtual void UpdateAnimation(float dt);
    virtual void Draw(float dt);

    virtual void OnCollision(Actor& actor);

    const Vector2 GetPosition();
    const Rectangle& GetCollider();
    const uint32_t GetCollisionLayer();
    const uint32_t GetCollisionMask();

protected:
    Vector2 oldPosition;
    Vector2 position;
    Vector2 direction = { 0, 0 };
    std::vector<Texture2D> animations;

    Rectangle collider;
    uint32_t collisionLayer;
    uint32_t collisionMask;

    float life = 100;
    int speed = 200;
    int animationSpeed = 6;
    int animationNumber = 1;
    float animationstate = 0;
    int animationIndex = 0;

    float height = 0.f;
    float width = 0.f;
    bool isMoving = false;
};
