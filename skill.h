#pragma once
#include "raylib.h"

class Actor;

class Skill
{
public:
	Skill(Actor& owner, float damage, float range, float cooldown);
	virtual ~Skill();

	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;

protected:
	Vector2 position;

	Actor& owner;

	float damage;
	float range;
	float cooldown;
};
