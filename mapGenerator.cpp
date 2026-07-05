#include "mapGenerator.h"
#include "utils.h"
#include "const.h"
#include <algorithm>

#include <cmath>


std::vector<TileType> MapGenerator::tilesmap(MAP_WIDTH* MAP_HEIGHT);


MapGenerator::MapGenerator()
{
	tilesNumber = MAP_WIDTH * MAP_HEIGHT;
}


std::vector<TileType> MapGenerator::GetRandomNavigationTilemap(int steps)
{
	int x = MAP_WIDTH / 2;
	int y = MAP_HEIGHT / 2;

	std::vector<TileType> tilemap(tilesNumber, TileType::WALL);

	tilemap[y * MAP_WIDTH + x] = TileType::FLOOR;

	for (int i = 1; i < steps; ++i)
	{
		int direction = GetRandomInt(0, 3);
		switch (direction)
		{
		case 0: x++; break;
		case 1: x--; break;
		case 2: y++; break;
		case 3: y--; break;
		default: break;
		}
		x = std::clamp(x, 0, MAP_WIDTH - 1);
		y = std::clamp(y, 0, MAP_HEIGHT - 1);

		tilemap[y * MAP_WIDTH + x] = TileType::FLOOR;
	}
	return tilemap;
}


void MapGenerator::GeneratePlaine()
{
	
}


void MapGenerator::GenerateCave()
{
	tilesmap = GetRandomNavigationTilemap(MAP_STEPS);
}


void MapGenerator::GenerateMap(MapType type)
{
	switch (type)
	{
	case MapType::PLAINE:
		GeneratePlaine();
		break;
	case MapType::CAVE:
		GenerateCave();
		break;
	default:
		break;
	}
}


void MapGenerator::DrawMap(Camera2D camera)
{
	Vector2 topLeftWorld = GetScreenToWorld2D({ 0, 0 }, camera);

	int startX = (int)(topLeftWorld.x / TILE_PIXEL) - 1;
	int startY = (int)(topLeftWorld.y / TILE_PIXEL) - 1;

	int horizontalTiles = SCREEN_WIDTH / TILE_PIXEL + 3;
	int verticalTiles = SCREEN_HEIGHT / TILE_PIXEL + 3;

	for (int y = startY; y < startY + verticalTiles; y++)
	{
		for (int x = startX; x < startX + horizontalTiles; x++)
		{
			if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
			{
				continue;
			}

			unsigned int tileIndex = y * MAP_WIDTH + x;

			Color color = (tilesmap[tileIndex] == TileType::FLOOR) ? LIGHTGRAY : DARKGRAY;

			DrawRectangle(x * TILE_PIXEL, y * TILE_PIXEL, TILE_PIXEL, TILE_PIXEL, color);
		}
	}
}


TileType MapGenerator::GetTile(int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH ||
		y < 0 || y >= MAP_HEIGHT)
	{
		return TileType::NONE;
	}
	return tilesmap[y * MAP_WIDTH + x];
}