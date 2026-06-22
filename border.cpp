#include "border.h"
#include "utils.h"

void Border::Init(Vector2 playerPosition)
{
    Actor::Init(playerPosition, "wall", 1);

    collisionLayer = static_cast<uint32_t>(ColliderLayer::MAP);
    collisionMask = static_cast<uint32_t>(ColliderLayer::PLAYER) | static_cast<uint32_t>(ColliderLayer::ENEMY);
}