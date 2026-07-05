#pragma once
#include <vector>
#include <raylib.h>


enum class TileType
{
	NONE,
	WALL,
	FLOOR,
};


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

	static TileType GetTile(int x, int y);

private:
	std::vector<TileType> GetRandomNavigationTilemap(int steps);

	void GeneratePlaine();
	void GenerateCave();

	static std::vector<TileType> tilesmap;

	int tilesNumber;
};
