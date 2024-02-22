#include "asteroid.h"

void Asteroid::generateDrawPoints() // more points when higher hp
{
	m_drawPoints.clear();

	int numPoints{GetRandomValue(2+m_hp, 5+m_hp)};
	if (numPoints > 10) numPoints = 10; // max for the shader is 10

	for (int i{}; i < numPoints; ++i)
	{
		float angle{i*(360/numPoints)};
		m_drawPoints.push_back(floatAngleToVec2(1 + static_cast<float>(getRandomFloat(-100, 100))/(2000), angle + getRandomFloat(-100, 100)/(2*numPoints))); // math to add some randomness
	}
}

std::vector<Vector2> Asteroid::getCurrentDrawPoints()
{
	std::vector<Vector2> output{};

	for (auto& p : m_drawPoints)
	{
		output.push_back(getRotatedVec2(pos() + p*rad(), pos(), rot()));
	}
	return output;
}

void Asteroid::init(InteractionData* id, int hp, Vector2 startPos, Vector2 vel, float rotVel, Color col)
{
	m_iData = id;

	m_startTime = id->bd.gt.currentTime();

	m_startPos = startPos;
	m_startRot = getRandomFloat(0, 360);

	m_vel = vel;
	m_rotVel = rotVel;

	m_hp = hp;

	m_col = col;

	generateDrawPoints();
}

void Asteroid::update()
{
	
}

void Asteroid::draw()
{
	std::vector<Vector2> points{getCurrentDrawPoints()};
	PolyLightShader::drawPolyLights(points, 1, m_col, m_iData->PLShad, m_iData->bd);
}