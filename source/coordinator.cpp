#include "coordinator.h"

void reset(GameData& g)
{
    g.wavShad.reset();
    g.astCont.reset();
    g.ship.reset();
    g.web.reset();
    g.explosions.reset();
    g.scoreCounter.reset();
    g.menu.reset();
}

void init(GameData& g)
{
    initID(g.iData);
    g.wavShad.init(&g.iData);
    g.astCont.init(&g.iData);
    g.ship.init(&g.iData);
    g.web.init(&g.iData);
    g.explosions.init(&g.iData);
    g.scoreCounter.init(&g.iData);
    g.menu.init(&g.iData);
    g.pprocessing.init(&g.iData);
    reset(g);
}

void update(GameData& g)
{
    if (!g.iData.paused)
    {
        g.wavShad.update();
        g.astCont.update();
        g.ship.update();
        g.web.update();
        g.explosions.update();
        g.scoreCounter.update();
        g.iData.bd.gt.unPause();
    }
    else
    {
        g.iData.bd.gt.pause();
    }
    g.menu.update();
    updateID(g.iData);

    if (g.iData.shouldRestart)
        reset(g);
}

void draw(GameData& g)
{
    //g.pprocessing.start();
	ClearBackground(BLACK);

    g.wavShad.draw();
    g.astCont.draw();
    g.ship.draw();
    g.web.draw();
    g.explosions.draw();
    g.scoreCounter.draw();
    g.menu.draw();
    drawID(g.iData);
    //g.pprocessing.end();
}