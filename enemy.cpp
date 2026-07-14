#include "enemy.h"
#include "utils.h"
#include "player.h"

Enemy::~Enemy() = default;


void Enemy::Init(Game& gameRef, Vector2 playerPosition, const Actor& actor)
{
    Actor::Init(gameRef, playerPosition, "warior", 1);
    target = &actor;

    collisionLayer = static_cast<uint32_t>(ColliderLayer::ENEMY);
    collisionMask = static_cast<uint32_t>(ColliderLayer::PLAYER) | static_cast<uint32_t>(ColliderLayer::MAP);
}


void Enemy::Update(float dt)
{
    auto targetPosition = target ->GetPosition();
    auto distance = GetDistanceV2(position, targetPosition);
    if (distance < triggerDistance && distance > rangeDistance)
    {
        direction.x = targetPosition.x - position.x;
        direction.y = targetPosition.y - position.y;
        direction = NormalizeV2(direction);
    }
    else
    {
        direction.x = 0;
        direction.y = 0;
    }
    Actor::Update(dt);

    if (attackCooldown > 0)
    {
        attackCooldown -= dt;
    }
}


void Enemy::OnCollision(Actor& actor)
{
    switch (static_cast<ColliderLayer>(actor.GetCollisionLayer()))
    {
    case ColliderLayer::PLAYER:
        if (attackCooldown <= 0)
        {
            Player& player = static_cast<Player&>(actor);
            player.TakeDamage(GetDamage());
            attackCooldown = attackSpeed;
        }
        break;
    }
}


float Enemy::GetDamage()
{
    return damage;
}