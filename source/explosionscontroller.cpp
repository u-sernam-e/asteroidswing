#include "explosionscontroller.h"
#include <cmath>

void ExplosionsController::init(InteractionData* id)
{
    m_iData = id;
}

void ExplosionsController::reset()
{
    m_iData->explosions.clear();
}

void ExplosionsController::update()
{
    for (int i{}; i < m_iData->explosions.size(); ++i)
    {
        if (m_iData->bd.gt.timeSince(m_iData->explosions[i].startTime) > M_EXPIRE_TIME)
        {
            m_iData->explosions.erase(m_iData->explosions.begin() + i);
            --i;
        }
    }
}

void ExplosionsController::draw()
{
    for (int i{}; i < m_iData->explosions.size(); ++i)
    {
        Explosion& e{m_iData->explosions[i]};
        float t{m_iData->bd.gt.timeSince(e.startTime) * 2};

        if (t > 1)
            t=1;

        for (int i{}; i < 8; ++i)
        {
            float radius{70};

            float startAmount{std::pow(t, .25)};
            float endAmount{std::pow(t, .5)};
            if (startAmount > 1)
                startAmount = 1;
            if (endAmount > 1)
                endAmount = 1;

            float angle = i*(360/8);

            DrawLineEx(e.pos + floatAngleToVec2(startAmount * radius, angle), e.pos + floatAngleToVec2(endAmount * radius, angle), 8, e.col);
        }
    }
}