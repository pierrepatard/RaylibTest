#pragma once
#include <vector>
#include <raylib.h>

enum class MapType
{
	PLAINE,
	CAVE,
	COUNT,
};


class MapGenerator
{
public:
	MapGenerator();

	void GenerateMap(MapType type);
	void DrawMap(Camera2D camera);

	unsigned int GetTile(int x, int y);

private:
	std::vector<unsigned int> GetRandomNavigationTilemap(int steps);

	void GeneratePlaine();
	void GenerateCave();

	std::vector<unsigned int> tilesmap;

	int tilesNumber;
};
