#include "basedata.h"
#include <iostream>

void initBD(BaseData& b)
{
	b.ts.init({"res/error.png", "res/1px.png", "res/space.png", "res/help.png", "res/lose.png", "res/pausebutton.png"});
    b.fs.init({"res/boleh.ttf"});
    b.ss.init({"res/ex1.wav", "res/web.wav", "res/lose.wav"}); 
    b.ms.init({}); 

    b.ui.init();
    b.gt.init();
}

void updateBD(BaseData& b)
{
    b.ui.update();
    b.gt.update();
}

void drawBD(BaseData& b)
{
    b.ui.draw();
}