#ifndef SCORECOUNTER
#define SCORECOUNTER
#include "interactiondata.h"

class ScoreCounter
{
    InteractionData* m_iData;
public:
    void init(InteractionData* iData) { m_iData = iData; }
    void reset() { m_iData->score.asteroidScore = 0; }
    void update()
    {
        if (!m_iData->ship.dead)
            m_iData->score.score = m_iData->score.asteroidScore + static_cast<int>(m_iData->bd.gt.timeSince(m_iData->ship.startTime) * 50);
    }
    void draw()
    {
        const char* text{TextFormat("%i", m_iData->score.score)};
        DrawTextEx(m_iData->bd.fs.get("res/boleh.ttf", 30), text, {getScreenSize().x/2 - MeasureTextEx(m_iData->bd.fs.get("res/boleh.ttf", 30), text, 30, 2).x, 10}, 30, 2, WHITE);
    }
};

#endif