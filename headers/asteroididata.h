#ifndef ASTEROIDIDATA
#define ASTEROIDIDATA
#include "rayextended.h"
#include <vector>

struct AsteroidIData
{
    Vector2 pos;
    float rad;
    int hp;
    
    bool shouldBeDestroyed;
};

#endif