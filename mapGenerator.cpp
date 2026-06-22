#include "mapGenerator.h"
#include "utils.h"
#include "const.h"
#include <algorithm>

#include <cmath>


MapGenerator::MapGenerator()
{
	tilesNumber = MAP_WIDTH * MAP_HEIGHT;
}


std::vector<unsigned int> MapGenerator::GetRandomNavigationTilemap(int steps)
{
	int x = MAP_WIDTH / 2;
	int y = MAP_HEIGHT / 2;

	std::vector<unsigned int> tilemap(tilesNumber, 0);

	tilemap[y * MAP_WIDTH + x] = 1;

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

		tilemap[y * MAP_WIDTH + x] = 1;
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


//void MapGenerator::DrawMap(Camera2D camera)
//{
//	auto horizontalTiles = ceil(SCREEN_WIDTH / TILE_PIXEL)+1;
//	auto verticalTiles = ceil(SCREEN_HEIGHT / TILE_PIXEL)+1;
//
//	auto pixelIndex = GetScreenToWorld2D({ SCREEN_CENTER_WIDTH, SCREEN_CENTER_HEIGHT }, camera);
//	auto tileIndex = 1;//find first tile
//
//	for (size_t i = 0; i < verticalTiles; ++i)
//	{
//		for (size_t j = 0; j < verticalTiles; ++j)
//		{
//			auto color = DARKGRAY;
//			if (tilesmap[tileIndex] == 1)
//			{
//				color = LIGHTGRAY;
//			}
//			else
//			{
//				bool adjacent = (tileIndex > 0 && tilesmap[tileIndex - 1] == 1);
//				adjacent |= (tileIndex + 1 < tilesmap.size() && tilesmap[tileIndex + 1] == 1);
//				adjacent |= (tileIndex > MAP_WIDTH && tilesmap[tileIndex - MAP_WIDTH] == 1);
//				adjacent |= (tileIndex + MAP_WIDTH < tilesmap.size() && tilesmap[tileIndex + MAP_WIDTH] == 1);
//				if (adjacent)
//				{
//					color = DARKGRAY;
//				}
//			}
//
//			auto y = tileIndex / MAP_WIDTH;
//			auto x = tileIndex % MAP_WIDTH;
//			DrawRectangle((x - MAP_CENTER_WIDTH) * TILE_PIXEL + SCREEN_CENTER_WIDTH, (y - MAP_CENTER_HEIGHT) * TILE_PIXEL + SCREEN_CENTER_HEIGHT, TILE_PIXEL, TILE_PIXEL, color);
//			tileIndex++;
//		}
//		tileIndex += horizontalTiles;
//	}
//}




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

			Color color = (tilesmap[tileIndex] == 1) ? LIGHTGRAY : DARKGRAY;

			DrawRectangle(x * TILE_PIXEL, y * TILE_PIXEL, TILE_PIXEL, TILE_PIXEL, color);
		}
	}
}


unsigned int MapGenerator::GetTile(int x, int y)
{
	if (x < 0 || x >= MAP_WIDTH ||
		y < 0 || y >= MAP_HEIGHT)
	{
		return 0;
	}
	return tilesmap[y * MAP_WIDTH + x];
}