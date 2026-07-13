#pragma once
#include "skill.h"


class Beam : public Skill
{
public:
    Beam(Actor& owner, float damage = 30, float range = 150.0f, float cooldown = 1.0f);

    void Update(float dt) override;
    void Draw(float dt) override;

private:
    float beamWidth = 8.0f;
    float cooldownTimer = 0.0f;
    Actor* target = nullptr;
};
