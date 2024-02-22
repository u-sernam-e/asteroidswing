#ifndef MENUS
#define MENUS
#include "interactiondata.h"

class Menus
{
    InteractionData* m_iData;

public:
    void init(InteractionData* iData);
    void reset();
    void update();
    void draw();
};

#endif