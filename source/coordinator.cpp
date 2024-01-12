#include "coordinator.h"

void init(GameData& g)
{
    initID(g.iData);
    g.astCont.init(&g.iData);
    g.ship.init(&g.iData);
}

void update(GameData& g)
{
    g.astCont.update();
    g.ship.update();
    updateID(g.iData);
}

void draw(GameData& g)
{
	ClearBackground(BLACK);

    g.astCont.draw();
    g.ship.draw();
    drawID(g.iData);

    if (IsKeyPressed(KEY_R))
        init(g);

    DrawFPS(10, 10);
}