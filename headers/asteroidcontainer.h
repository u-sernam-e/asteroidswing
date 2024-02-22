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
    void spawnAsteroidChildren(Vector2 pos, int hp, Color col);

    void playRandomExplosionSound();
    
    void destroyAsteroid(int index);
    void explodeAsteroid(int index);
public:
    void init(InteractionData* id);
    void reset();
    void update() override;
    void draw() override;
};

#endif