#pragma once
#include <vector>
#include <memory>

#include "actor.h"


class CollisionSystem
{
public:
    static void CheckCollisions(const std::vector<std::unique_ptr<Actor>>& actors);
};