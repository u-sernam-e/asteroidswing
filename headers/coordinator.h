#ifndef COORDINATOR
#define COORDINATOR 
#include "basedata.h"
#include "interactiondata.h"
#include "asteroidcontainer.h"
#include "ship.h"
#include "waveshader.h"
#include "explosionscontroller.h"
#include "menus.h"
#include "scorecounter.h"
#include "postprocessing.h"

// so this file is  the general game coordination,
// controlling what scene the program is in and updating and drawing
// things accordingly

struct GameData
{
    InteractionData iData;
    AsteroidContainer astCont;
    ExplosionsController explosions;
    Ship ship;
    Web web;
    WaveShader wavShad;
    Menus menu;
    ScoreCounter scoreCounter;
    PostProcessing pprocessing;
};

void init(GameData& g);
void update(GameData& g);
void draw(GameData& g);

#endif