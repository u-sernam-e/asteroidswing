#ifndef SHIP
#define SHIP
#include "interactiondata.h"
#include "web.h"

class Ship : public Ob
{
private:
    InteractionData* m_iData;

    Web m_web;

    Vector2 m_pos;
    Vector2 m_vel;
    Vector2 m_prevVel;

    const float M_GRAVITY{5};
    const float M_BOOSTSTRENGTH{0.02};

    std::vector<Vector2> generateDrawPoints();
    Vector2 getChangeInVel();

    void updateWeb();
public:
    void init(InteractionData* id);
    void update() override;
    void draw() override;
};

#endif