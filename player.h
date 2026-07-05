#pragma once
#include "raylib.h"
#include <math.h>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <cmath>
#include <string>

#include "actor.h"


class Player: public Actor
{
public:
    Player();
    ~Player();
    void Init(Vector2 playerPosition);
    void Update(float dt) override;
    void Draw(float dt) override;

    void OnCollision(Actor& actor) override;

    void TakeDamage(float damage);
private:
    void RegisterPlayerBinding();

    Texture2D dash;

    float dashLengh = 100;
    int quaterSize = 12;
    float dashPhase = 0;
};
