#include "utils.h"
#include <cmath>
#include <iostream>
#include <random>
#include "raylib.h"


int GetRandomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(min, max);
    return distr(gen);
}


Vector2 NormalizeV2(Vector2 v)
{
    float length = v.x * v.x + v.y * v.y;

    if (length == 0.0f)
        return { 0.0f, 0.0f };

    float invLength = 1.0f / std::sqrt(length);
    return {
        v.x *= invLength,
        v.y *= invLength
    };
}


int GetDistanceV2(Vector2 v1, Vector2 v2)
{
    return std::hypot(v1.x - v2.x, v1.y - v2.y);
}


void Print(std::string string)
{
    std::cout << string << std::endl;
}


void Print(int number)
{
    std::cout << std::to_string(number) << std::endl;
}