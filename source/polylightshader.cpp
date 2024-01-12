#include "polylightshader.h"

void PolyLightShader::init(PolyLightShader& PLShad)
{
	if (IsShaderReady(PLShad.shad))
		UnloadShader(PLShad.shad);

    PLShad.shad = LoadShader(0, "res/shader/330/polylightshader.fs");

	for (int i{}; i < PLShad.pointsLoc.size(); ++i)
	{
		PLShad.pointsLoc[i] = GetShaderLocation(PLShad.shad, TextFormat("points[%i]", i));
	}
    PLShad.numPointsLoc = GetShaderLocation(PLShad.shad, "numPoints");
    PLShad.brightnessLoc = GetShaderLocation(PLShad.shad, "brightness");
    PLShad.aspectRatioLoc = GetShaderLocation(PLShad.shad, "aspectRatio");
}

void PolyLightShader::drawPolyLights(std::vector<Vector2> points, float brightness, Color col, PolyLightShader& PLShad, BaseData& bd)
{
	int numPoints{points.size()};
	SetShaderValue(PLShad.shad, PLShad.numPointsLoc, &numPoints, SHADER_UNIFORM_INT);

	float aspectRatio{getScreenSize().x/getScreenSize().y};
	SetShaderValue(PLShad.shad, PLShad.aspectRatioLoc, &aspectRatio, SHADER_UNIFORM_FLOAT);

	SetShaderValue(PLShad.shad, PLShad.brightnessLoc, &brightness, SHADER_UNIFORM_FLOAT);

	for (int i{}; i < numPoints; ++i)
	{
		Vector2 point{points[i]/getScreenSize()};
		SetShaderValue(PLShad.shad, PLShad.pointsLoc[i], &point, SHADER_UNIFORM_VEC2);
	}

	BeginShaderMode(PLShad.shad);
	DrawTexturePro(bd.ts.get("res/1px.png"), {0, 0, 1, 1}, {0, 0, getScreenSize().x, getScreenSize().y}, {0, 0}, 0, col);
	EndShaderMode();
}