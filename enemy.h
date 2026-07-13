#pragma once
#include "actor.h"

class Enemy: public Actor
{
public:
    ~Enemy() override;

    void Init(Game& gameRef, Vector2 playerPosition, Actor& actor);
    void Update(float dt) override;

    void OnCollision(Actor& actor) override;

    float GetDamage();
private:
    Actor* target = nullptr;
    float triggerDistance = 200;
    float rangeDistance = 20;

    float damage = 10;
    float attackSpeed = 1.f;
    float attackCooldown = 0;
    
};