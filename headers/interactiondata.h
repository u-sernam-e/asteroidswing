#ifndef INTERACTIONDATA
#define INTERACTIONDATA 
#include "basedata.h"
#include "polylightshader.h"
#include "asteroididata.h"

// this struct can be used by classes to talk to each other by setting variables in structs that they can all see

struct InteractionData
{
    BaseData bd;
    PolyLightShader PLShad;
    std::vector<AsteroidIData> asteroids;
};

void initID(InteractionData& id);
void updateID(InteractionData& id);
void drawID(InteractionData& id);

#endif