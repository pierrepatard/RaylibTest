#include "collisionSystem.h"


bool ShouldCollide(Actor& a, Actor& b)
{
    return (a.GetCollisionMask() & b.GetCollisionLayer()) && (b.GetCollisionMask() & a.GetCollisionLayer());
}


void CollisionSystem::CheckCollisions(Actor& player, const std::vector<std::unique_ptr<Actor>>& actors)
{
    for (size_t i = 0; i < actors.size(); i++)
    {
        if (ShouldCollide(*actors[i], player) && CheckCollisionRecs(actors[i]->GetCollider(), player.GetCollider()))
        {
            actors[i]->OnCollision(player);
            player.OnCollision(*actors[i]);
        }
        for (size_t j = i + 1; j < actors.size(); j++)
        {
            if (ShouldCollide(*actors[i], *actors[j]) && CheckCollisionRecs(actors[i]->GetCollider(),actors[j]->GetCollider()))
            {
                actors[i]->OnCollision(*actors[j]);
                actors[j]->OnCollision(*actors[i]);
            }
        }
    }
}