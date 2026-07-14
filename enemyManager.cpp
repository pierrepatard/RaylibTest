#include "actor.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "utils.h"

#include "enemyManager.h"


std::vector< std::unique_ptr<Actor>> EnemyManager::SpawnEnemies(Game* game, int number)
{
	std::vector< std::unique_ptr<Actor>> enemies;

	for (int i = 0; i < number; i++)
	{
		auto enemy = std::make_unique<Enemy>();

		bool isColliding = true;
		int attempts = 5;
		do
		{
			float xposition = (MAP_CENTER_WIDTH + GetRandomInt(5, 10)) * TILE_PIXEL;
			float yposition = (MAP_CENTER_HEIGHT + GetRandomInt(5, 10)) * TILE_PIXEL;
			isColliding = IsMapColliding(xposition, yposition, enemy->GetWidth(), enemy->GetHeight());
			if (!isColliding)
			{
				enemy->Init(*game, { xposition, yposition }, game->GetPlayerActor());
				enemies.push_back(std::move(enemy));
			}
			else
			{
				attempts--;
			}
		}
		while (isColliding && attempts > 0);
		if (attempts == 0)
		{
			Print("Unable To spawn enemy");
		}
	}

	return enemies;
}