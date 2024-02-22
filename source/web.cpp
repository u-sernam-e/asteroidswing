#include "web.h"
#include <cmath>

void Web::init(InteractionData* id)
{
    m_iData = id;
}

void Web::reset()
{
    m_startPos = {0, 0};
    m_endPos = {0, 0};

    m_startTime = m_iData->bd.gt.currentTime();
    m_active = false;
}

Vector2 Web::counterClockPoint()
{
	return m_iData->ship.pos + floatAngleToVec2(M_LENGTH, vec2ToAngle(m_iData->ship.vel) + 90);
}
Vector2 Web::clockPoint()
{
	return m_iData->ship.pos + floatAngleToVec2(M_LENGTH, vec2ToAngle(m_iData->ship.vel) - 90);
}

std::vector<Vector2> Web::generateDrawPoints()
{
	std::vector<Vector2> output{m_startPos, m_endPos};

	std::vector<Vector2> shipPoints{m_iData->ship.drawPoints};

	for (int i{}; i < shipPoints.size(); ++i)
	{
		if (CheckCollisionLines(m_startPos, m_endPos, shipPoints[i], shipPoints[(i+1)%shipPoints.size()], &output[0]))
			break;
	}

	float timeSince{m_iData->bd.gt.timeSince(m_startTime) * 5};
	if (timeSince > 1) timeSince = 1;
	float amountOnLine{70*std::pow(timeSince, 9) - 315*std::pow(timeSince, 8) + 540*std::pow(timeSince, 7) - 420*std::pow(timeSince, 6) + 126*std::pow(timeSince, 5)}; // smoothstep on wikipedia
	output[1] = m_startPos + (m_endPos - m_startPos) * amountOnLine;

	return output;
}

void Web::updateIData()
{
    m_iData->web.startPos = m_startPos;
    m_iData->web.endPos = m_endPos;

    m_iData->web.length = M_LENGTH;

	m_iData->web.clockPos = clockPoint();
	m_iData->web.counterClockPos = counterClockPoint();

    m_iData->web.active = m_active;
	m_iData->web.justFired = m_justFired;
	m_iData->web.clockwise = m_clockwise;

    m_iData->web.drawPoints = generateDrawPoints();
}

void Web::playSound()
{
	PlaySound(m_iData->bd.ss.get("res/web.wav"));
}

void Web::updateWeb()
{
    m_startPos = m_iData->ship.pos;

	m_justFired = false;

	if (m_active)
	{
		if (m_mouseUsed)
		{
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				m_active = false;
		}
		else
		{
			if (IsKeyReleased(m_keyUsed)) // may be buggy
				m_active = false;
		}
	}
	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMousePosition().x < getScreenSize().x/2))
	{
		m_active = true;
		m_clockwise = false;
		m_justFired = true;
		m_startTime = m_iData->bd.gt.currentTime();
		m_endPos = clockPoint();

		m_keyUsed = GetKeyPressed();
		m_mouseUsed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
		playSound();
	}
	if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMousePosition().x > getScreenSize().x/2))
	{
		m_active = true;
		m_clockwise = true;
		m_justFired = true;
		m_startTime = m_iData->bd.gt.currentTime();
		m_endPos = counterClockPoint();

		m_keyUsed = GetKeyPressed();
		m_mouseUsed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
		playSound();
	}
}

void Web::destroyAsteroids()
{
	for (auto& a : m_iData->asteroids)
	{
		if (checkCollisionCircleLine(m_startPos, m_endPos, a.pos, a.rad) && m_iData->bd.gt.timeSince(a.startTime) > a.invincibleTime)
			--a.hp;
	}
}

void Web::update()
{
	if (!m_iData->ship.dead)
	{
		updateWeb();
		if (m_active)
			destroyAsteroids();
	}
	updateIData();
}

void Web::draw()
{
	if (!m_iData->ship.dead)
	{
		if (m_active)
			PolyLightShader::drawPolyLights(generateDrawPoints(), 0.5, WHITE, m_iData->PLShad, m_iData->bd);
		else
		{
			DrawCircleGradient(clockPoint().x, clockPoint().y, 10, RED, {0, 0, 0, 0});
			DrawCircleGradient(counterClockPoint().x, counterClockPoint().y, 10, RED, {0, 0, 0, 0});
		}
	}
}