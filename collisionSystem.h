#pragma once
#include <vector>
#include <memory>

#include "actor.h"

class CollisionSystem
{
public:
    static void CheckCollisions(Actor& player, const std::vector<std::unique_ptr<Actor>>& actors);
};