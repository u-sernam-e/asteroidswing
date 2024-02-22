#include "asteroidcontainer.h"

void AsteroidContainer::initNewAsteroidIData()
{
	m_iData->asteroids.push_back({
		m_asteroids[m_asteroids.size()-1].pos(),
		m_asteroids[m_asteroids.size()-1].rad(),
		m_asteroids[m_asteroids.size()-1].hp(),
		m_iData->bd.gt.currentTime(),
		1,
		false
	});
}

void AsteroidContainer::updateAsteroidIData()
{
	if (m_asteroids.size() == m_iData->asteroids.size())
	{
		for (int i{}; i < m_asteroids.size(); ++i)
		{
			m_iData->asteroids[i].pos = m_asteroids[i].pos();
			m_iData->asteroids[i].rad = m_asteroids[i].rad();
			m_iData->asteroids[i].hp = m_asteroids[i].hp();
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
	m_asteroids[m_asteroids.size()-1].init(m_iData, asteroidHP, pos, vel, getRandomFloat(-100, 100), randomSaturatedColor());

	initNewAsteroidIData();
}

void AsteroidContainer::spawnAsteroidChildren(Vector2 pos, int hp, Color col)
{
	float angle{getRandomFloat(0, 360)};
	for (int i{}; i < 3; ++i)
	{
		Vector2 vel{floatAngleToVec2(getRandomFloat(50, 100), angle + i*(360/3))};
			
		m_asteroids.push_back({});
		m_asteroids[m_asteroids.size()-1].init(m_iData, hp - 1, pos, vel, getRandomFloat(-100, 100), col);

		initNewAsteroidIData();
	}
}

void AsteroidContainer::destroyAsteroid(int index)
{
	m_iData->asteroids.erase(m_iData->asteroids.begin() + index);
	m_asteroids.erase(m_asteroids.begin() + index);
}

void AsteroidContainer::playRandomExplosionSound()
{
	PlaySound(m_iData->bd.ss.get("res/ex1.wav"));
}

void AsteroidContainer::explodeAsteroid(int index) // for when it is exploded by player
{
	playRandomExplosionSound();
	m_iData->score.asteroidScore += m_asteroids[index].hp() * 100;
	m_iData->explosions.push_back({m_iData->bd.gt.currentTime(), m_asteroids[index].pos(), getBrighterColor(m_asteroids[index].col(), 4)});
	if (m_asteroids[index].hp() > 1)
		spawnAsteroidChildren(m_asteroids[index].pos(), m_asteroids[index].hp(), m_asteroids[index].col());
}

void AsteroidContainer::init(InteractionData* id)
{
	m_iData = id;
	
	m_lastAsteroidTime = 0;
	m_spawnRate = 1.5;
}

void AsteroidContainer::reset()
{
	m_iData->asteroids.clear();
	
	m_asteroids.clear();
	
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

		if (m_iData->asteroids[i].hp == m_asteroids[i].hp() - 1)
		{
			explodeAsteroid(i);
			destroyAsteroid(i);
			--i;
		}
		else if (m_asteroids[i].isOutOfBounds())
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