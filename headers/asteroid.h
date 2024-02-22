#ifndef ASTEROID
#define ASTEROID
#include "interactiondata.h"

class Asteroid : public Ob
{
private:
    InteractionData* m_iData{};
    
    Vector2 m_startPos;
    float m_startRot;
    float m_startTime;

    Vector2 m_vel;
    float m_rotVel;

    int m_hp;

    Color m_col;

    std::vector<Vector2> m_drawPoints;
    void generateDrawPoints();
    std::vector<Vector2> getCurrentDrawPoints();
    Color randomColor();
public:
    static float getAsteroidHPSizeMultiplier() { return 8; }

    Vector2 pos() { return m_startPos + m_vel*(m_iData->bd.gt.timeSince(m_startTime)); }
    float rot() { return m_startRot + m_rotVel*(m_iData->bd.gt.timeSince(m_startTime)); }
    int hp() { return m_hp; }
    float rad() { return m_hp*getAsteroidHPSizeMultiplier(); }
    Color col() { return m_col; }
    bool isOutOfBounds() { return pos().x < -rad() - 20 || pos().x > getScreenSize().x + rad() + 20 || pos().y < -rad() - 20 || pos().y > getScreenSize().y + rad() + 20; }

    void init(InteractionData* id, int hp, Vector2 startPos, Vector2 vel, float rotVel, Color col);
    void update() override;
    void draw() override;
};

#endif