#include "game.h"
#include "actor.h"
#include "raymath.h"
#include "Beam.h"
#include "utils.h"


Beam::Beam(Actor& owner, float damage, float range, float cooldown) : Skill(owner, damage, range, cooldown)
{
}


void Beam::Update(float dt)
{
    target = nullptr;

    float bestDistance = range;

   for (const auto& other : owner.GetGame()->GetActors())
   {
        if (other.get() == &owner)
            continue;

        float distance = fabsf(Vector2Distance( owner.GetPosition(), other->GetPosition()));

        if (distance < bestDistance)
        {
            bestDistance = distance;
            target = other.get();
        }
   }

   if (target != nullptr)
   {
       if (cooldownTimer > 0)
       {
           cooldownTimer -= dt;
       }
       else
       {
            target->TakeDamage(damage);
            if (!target->IsAlive())
            {
                target == nullptr;
            }
            cooldownTimer = cooldown;
       }
   }
}


void Beam::Draw(float dt)
{
    if (target == nullptr)
        return;

    DrawLineEx( owner.GetCenteredPosition(), target->GetCenteredPosition(), beamWidth * cooldownTimer, RED);
}