#pragma once

#include "raylib.h"
#include <sstream>

enum class ColliderLayer: uint32_t
{
	MAP = 1 << 0,
	PLAYER = 1 << 1,
	ENEMY = 1 << 2,
};

int GetRandomInt(int min, int max);
Vector2 NormalizeV2(Vector2 v);
int GetDistanceV2(Vector2 v1, Vector2 v2);
void Print(std::string string);
void Print(int number);
bool IsMapColliding(int x, int y, float width, int height);
