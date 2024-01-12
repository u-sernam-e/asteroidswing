#include "ship.h"
#include <cmath>

Vector2 Ship::getChangeInVel()
{
	return (m_vel - m_prevVel)/lowerLimitFrameTime();
}

std::vector<Vector2> Ship::generateDrawPoints()
{
	float stretchAmount{std::pow(1.01, getRotatedVec2(getChangeInVel(), {0, 0}, vec2ToAngle(m_vel)).x)};
	if (stretchAmount > 2) stretchAmount = 2;
	if (stretchAmount < .5) stretchAmount = 0.5;

	std::vector<Vector2> output{
		m_pos + Vector2{20*stretchAmount, 0},
		m_pos + Vector2{-15*stretchAmount, 10/stretchAmount},
		m_pos + Vector2{-10*stretchAmount, 0},
		m_pos + Vector2{-15*stretchAmount, -10/stretchAmount}
	};

	for (auto& p : output)
	{
		p = getRotatedVec2(p, m_pos, vec2ToAngle(m_vel));
	}

	return output;
}

std::vector<Vector2> Ship::generateWebDrawPoints()
{
	std::vector<Vector2> output{m_pos, m_webPos};
	output[1] = m_webPos;

	std::vector<Vector2> shipPoints{generateDrawPoints()};

	for (int i{}; i < shipPoints.size(); ++i)
	{
		if (CheckCollisionLines(m_pos, m_webPos, shipPoints[i], shipPoints[(i+1)%shipPoints.size()], &output[0]))
			break;
	}
	return output;
}

void Ship::init(InteractionData* id)
{
	m_iData = id;
	
	m_pos = getScreenSize()/2;
	m_vel = {0, 0};
	m_prevVel = {0, 0};

	m_web.init();
}

void Ship::updateWeb()
{
	if (m_webActive)
	{
		Vector2 webVec{m_webPos - m_pos};

		if (vec2ToFloat(webVec) > m_webTautLength)
			m_vel += normalizedVec2(webVec) * (vec2ToFloat(webVec) - m_webTautLength) * M_WEBSTRENGTH * lowerLimitFrameTime();

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			m_webActive = false;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || GetTouchPointCount() > 1)
		{
			m_webActive = false;
			m_vel = webVec * M_BOOSTSTRENGTH;
		}
	}
	else
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			m_webActive = true;
			m_webStartTime = m_iData->bd.gt.currentTime();
			m_webPos = GetMousePosition();
			m_webTautLength = vec2distance(m_webPos, m_pos);
		}
	}
}

void Ship::update()
{
	m_prevVel = m_vel;
	
	updateWeb();

	m_vel.y += M_GRAVITY * lowerLimitFrameTime();
	m_pos += m_vel;
}

void Ship::draw()
{
	PolyLightShader::drawPolyLights(generateDrawPoints(), 0.75, BLUE, m_iData->PLShad, m_iData->bd);
	if (m_webActive)
		PolyLightShader::drawPolyLights(generateWebDrawPoints(), 0.5, WHITE, m_iData->PLShad, m_iData->bd);
}