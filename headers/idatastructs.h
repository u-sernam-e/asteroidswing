#ifndef IDATASTRUCTS
#define IDATASTRUCTS
#include "rayextended.h"

struct ShipIData
{
    Vector2 pos;
    Vector2 vel;

    bool dead;
    float deathTime;

    float startTime;

    std::vector<Vector2> drawPoints;
};

struct WebIData
{
    Vector2 startPos;
    Vector2 endPos;

    float length;

    Vector2 clockPos;
    Vector2 counterClockPos;

    bool active;
    bool justFired;
    bool clockwise;

    std::vector<Vector2> drawPoints;
};

struct AsteroidIData
{
    Vector2 pos;
    float rad;
    int hp;

    float startTime;
    float invincibleTime;
    
    bool shouldBeDestroyed;
};

struct Explosion
{
    float startTime;
    Vector2 pos;
    Color col;
};

struct ScoreIData
{
    int asteroidScore;
    int score;
};

#endif