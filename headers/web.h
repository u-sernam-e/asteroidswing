#ifndef WEB
#define WEB
#include "interactiondata.h"

class Web : public Ob
{
    Vector2 m_startPos;
    Vector2 m_endPos;

    float m_startTime;
    bool m_active;
    float m_tautLength;

    const float M_STRENGTH{0.5};

    std::vector<Vector2> generateDrawPoints(Web& w, );
};

#endif