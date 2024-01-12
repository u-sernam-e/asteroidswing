#include "asteroidcontainer.h"

void AsteroidContainer::initNewAsteroidIData()
{
	m_iData->asteroids.push_back({
		m_asteroids[m_asteroids.size()-1].pos(),
		m_asteroids[m_asteroids.size()-1].rad(),
		m_asteroids[m_asteroids.size()-1].hp(),
		false
	});
}

void AsteroidContainer::updateAsteroidIData()
{
	if (m_asteroids.size() == m_iData->asteroids.size())
	{
		for (int i{}; i < m_asteroids.size(); ++i)
		{
			m_iData->asteroids[i].pos = m_asteroids[i].pos(); // update pos

			if (m_iData->asteroids[i].shouldBeDestroyed) // if the asteroid should be destroyed
			{
				destroyAsteroid(i);
				--i;
			}
		}
	}
	else
		std::cout << "asteroid vector and asteroid idata vector are different sizes (this should not be the case... *_*)\n";
}

void AsteroidContainer::spawnAsteroid()
{
	int asteroidHP{GetRandomValue(2, 4)};

	bool topOrBot{GetRandomValue(0, 1)}; // false if it spawns on the left/right sides
	bool reflect{GetRandomValue(0, 1)}; // if true, it will be on the right or on the bottom
	float distanceFromEdge{asteroidHP * Asteroid::getAsteroidHPSizeMultiplier() + 20};

	Vector2 pos{(topOrBot ? getRandomFloat(0, getScreenSize().x) : (reflect ? -distanceFromEdge : getScreenSize().x + distanceFromEdge)), (topOrBot ? (reflect ? -distanceFromEdge : getScreenSize().y + distanceFromEdge) : getRandomFloat(0, getScreenSize().y))};
	Vector2 vel{floatAngleToVec2(getRandomFloat(50, 100), vec2ToAngle(getScreenSize()/2 - pos) + getRandomFloat(-45, 45))};


	m_asteroids.push_back({});
	m_asteroids[m_asteroids.size()-1].init(m_iData, asteroidHP, pos, vel, getRandomFloat(-100, 100));

	initNewAsteroidIData();
}

void AsteroidContainer::destroyAsteroid(int index) // in here it has to spawn 3 new asteroids and trigger some sort of particle effect, u can do that afer u make the player
{
	m_iData->asteroids.erase(m_iData->asteroids.begin() + index);
	m_asteroids.erase(m_asteroids.begin() + index);
}

void AsteroidContainer::init(InteractionData* id)
{
	m_iData = id;

	id->asteroids.clear();
	
	m_asteroids.clear();
	
	m_lastAsteroidTime = 0;
	m_spawnRate = 3;
}

void AsteroidContainer::update()
{
	if (m_iData->bd.gt.timeSince(m_lastAsteroidTime) > m_spawnRate) // spawn an asteroid after spawnrate time has elapsed
	{
		spawnAsteroid();
		m_lastAsteroidTime = m_iData->bd.gt.currentTime();
	}

	for (int i{}; i < m_asteroids.size(); ++i)
	{
		m_asteroids[i].update();

		if(m_asteroids[i].isOutOfBounds())
		{
			destroyAsteroid(i);
			--i;
		}
	}

	updateAsteroidIData();
}

void AsteroidContainer::draw()
{
	for (auto& a : m_asteroids)
	{
		a.draw();
	}
} 