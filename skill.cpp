
#include "skill.h"

Skill::Skill(Actor& owner, float damage, float range, float cooldown): owner(owner), damage(damage), range(range), cooldown(cooldown)
{
}


Skill::~Skill() = default;
