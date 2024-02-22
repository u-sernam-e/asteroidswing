#ifndef INTERACTIONDATA
#define INTERACTIONDATA 
#include "basedata.h"
#include "polylightshader.h"
#include "idatastructs.h"

// this struct can be used by classes to talk to each other by setting variables in structs that they can all see

struct InteractionData
{
    BaseData bd;
    PolyLightShader PLShad;
    std::vector<Explosion> explosions;
    std::vector<AsteroidIData> asteroids;
    ShipIData ship;
    WebIData web;
    ScoreIData score;
    bool paused;
    bool shouldRestart;
};

void initID(InteractionData& id);
void updateID(InteractionData& id);
void drawID(InteractionData& id);

#endif