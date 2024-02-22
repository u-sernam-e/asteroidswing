#ifndef SHIP
#define SHIP
#include "interactiondata.h"
#include "web.h"

class Ship : public Ob
{
private:
    InteractionData* m_iData;

    Vector2 m_pos;
    float m_angle;

    Vector2 m_vel;
    Vector2 m_prevVel;

    bool m_unClockwise;

    bool m_dead;
    float m_deathTime;
    
    float m_startTime;

    const float M_STARTSPEED{370};

    std::vector<Vector2> generateDrawPoints();
    float speed();
    Vector2 vel();

    void movePositionToOnScreen();

    void updateBounces();
    void updateMovement();
    void updateCollision();
    void updateIData();
public:
    void init(InteractionData* id);
    void reset();
    void update() override;
    void draw() override;
};

#endif