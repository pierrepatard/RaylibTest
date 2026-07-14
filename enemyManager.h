#pragma once


class Actor;
class Game;

class EnemyManager
{
public:
	std::vector< std::unique_ptr<Actor>> SpawnEnemies(Game* game, int number);
};
