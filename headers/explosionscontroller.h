#ifndef EXPLOSIONSCONTROLLER
#define EXPLOSIONSCONTROLLER
#include "interactiondata.h"


class ExplosionsController : public Ob
{
    InteractionData* m_iData;

    const float M_EXPIRE_TIME{1};
public:
    void init(InteractionData* id);
    void reset();
    void update() override;
    void draw() override;
};

#endif