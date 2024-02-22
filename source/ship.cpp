#include "ship.h"
#include <cmath>

void Ship::init(InteractionData* id)
{
	m_iData = id;
}

void Ship::reset()
{
	m_pos = getScreenCenter();
	m_angle = 0;

	m_dead = false;
	
	m_startTime = m_iData->bd.gt.currentTime();
}

float Ship::speed()
{
	return M_STARTSPEED + m_iData->bd.gt.timeSince(m_startTime) * 1.5;
}

Vector2 Ship::vel()
{
	return floatAngleToVec2(speed(), m_angle);
}

std::vector<Vector2> Ship::generateDrawPoints()
{
	std::vector<Vector2> output{
		m_pos + Vector2{15, 0},
		m_pos + Vector2{-10, 10},
		m_pos + Vector2{-7, 0},
		m_pos + Vector2{-10, -10}
	};

	for (auto& p : output)
	{
		p = getRotatedVec2(p, m_pos, m_angle);
	}

	return output;
}

void Ship::updateIData()
{
	m_iData->ship.pos = m_pos;
	m_iData->ship.vel = vel();

	m_iData->ship.dead = m_dead;
	m_iData->ship.deathTime = m_deathTime;

	m_iData->ship.startTime = m_startTime;

	m_iData->ship.drawPoints = generateDrawPoints();
}

void Ship::movePositionToOnScreen()
{
	if (m_pos.x < 0)
		m_pos.x = 0;
	else if (m_pos.x > getScreenSize().x)
		m_pos.x = getScreenSize().x;

	if (m_pos.y < 0)
		m_pos.y = 0;
	else if (m_pos.y > getScreenSize().y)
		m_pos.y = getScreenSize().y;
}

void Ship::updateBounces()
{
	if ((m_pos.x < 0 && vel().x < 0) || (m_pos.x > getScreenSize().x && vel().x > 0) || (m_pos.y < 0 && vel().y < 0) || (m_pos.y > getScreenSize().y && vel().y > 0))
	{
		float newAngle{m_angle};
		if ((m_pos.y < 0 && vel().y < 0) || (m_pos.y > getScreenSize().y && vel().y > 0))
			newAngle -= 180;
			
		if (m_angle < 180)
			newAngle -= 180;
		newAngle -= 90;
		newAngle = -newAngle;
		newAngle += 90;
		if (m_angle < 180)
			newAngle += 180;
	
		if (m_iData->web.active)
		{
			m_unClockwise = !m_unClockwise;
			if (!isPointOnScreen(m_iData->web.endPos))
				newAngle = m_angle - 180;
		}
		
		m_angle = newAngle;

		movePositionToOnScreen();
	}

	if (!m_iData->web.active || m_iData->web.justFired)
		m_unClockwise = false;
}

void Ship::updateMovement()
{
	if (m_iData->web.active)
	{
		float angleAdd = (speed()*lowerLimitFrameTime()*RAD2DEG)/m_iData->web.length;
		if (!m_iData->web.clockwise != m_unClockwise)
			angleAdd = -angleAdd;

		m_angle += angleAdd;
	}
	
	m_pos += vel() * lowerLimitFrameTime();
}

void Ship::updateCollision()
{
	for (auto& a : m_iData->asteroids)
	{
		if (CheckCollisionPointCircle(m_pos, a.pos, a.rad) && !m_dead)
		{
			m_iData->explosions.push_back({m_iData->bd.gt.currentTime(), m_pos, WHITE});
			m_deathTime = m_iData->bd.gt.currentTime();
			m_dead = true;
			PlaySound(m_iData->bd.ss.get("res/lose.wav"));
		}
	}
}

void Ship::update()
{
	if (!m_dead)
	{
		updateBounces();
		updateMovement();
		updateCollision();
	}

	updateIData();
}

void Ship::draw()
{
	if (!m_dead)
		PolyLightShader::drawPolyLights(generateDrawPoints(), 0.6, BLUE, m_iData->PLShad, m_iData->bd);
}