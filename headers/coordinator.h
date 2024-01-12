#ifndef COORDINATOR
#define COORDINATOR 
#include "basedata.h"
#include "interactiondata.h"
#include "asteroidcontainer.h"
#include "ship.h"

// so this file is  the general game coordination,
// controlling what scene the program is in and updating and drawing
// things accordingly

struct GameData
{
    BaseData bData;
    InteractionData iData;
    AsteroidContainer astCont;
    Ship ship;
};

void init(GameData& g);
void update(GameData& g);
void draw(GameData& g);

#endif