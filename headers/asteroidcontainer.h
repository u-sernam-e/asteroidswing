#ifndef ASTEROIDCONTAINER
#define ASTEROIDCONTAINER
#include "interactiondata.h"
#include "asteroid.h"

class AsteroidContainer : public Ob
{
private:
    InteractionData* m_iData{};

    std::vector<Asteroid> m_asteroids{};

    float m_lastAsteroidTime;
    float m_spawnRate;

    void initNewAsteroidIData();
    void updateAsteroidIData();

    void spawnAsteroid();
    void destroyAsteroid(int index);
public:
    void init(InteractionData* id);
    void update() override;
    void draw() override;
};

#endif