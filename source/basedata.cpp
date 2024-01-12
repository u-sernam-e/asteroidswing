#include "basedata.h"
#include <iostream>

void initBD(BaseData& b)
{
	b.ts.init({"res/error.png", "res/1px.png"});
    b.fs.init({});
    b.ss.init({}); 
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