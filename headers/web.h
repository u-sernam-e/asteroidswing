#ifndef WEB
#define WEB
#include "interactiondata.h"

class Web : public Ob
{
private:
    InteractionData* m_iData;

    Vector2 m_startPos;
    Vector2 m_endPos;

    float m_startTime;
    bool m_active;
    bool m_justFired;
    bool m_clockwise;

    int m_keyUsed;
    bool m_mouseUsed;

    const float M_LENGTH{170};

    void updateIData();
    void updateWeb();
    void destroyAsteroids();

    Vector2 counterClockPoint();
    Vector2 clockPoint();
    std::vector<Vector2> generateDrawPoints();

    void playSound();
public:
    void init(InteractionData* id);
    void reset();
    void update() override;
    void draw() override;
};

#endif