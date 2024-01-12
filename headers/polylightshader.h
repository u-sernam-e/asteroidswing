#ifndef POLYLIGHTSHADER
#define POLYLIGHTSHADER
#include "rayextended.h"
#include "basedata.h"
#include <array>
#include <vector>

struct PolyLightShader
{
    Shader shad;
    std::array<unsigned int, 10> pointsLoc;
    unsigned int numPointsLoc;
    unsigned int brightnessLoc;
    unsigned int aspectRatioLoc;

    static void init(PolyLightShader& PLShad);
    static void drawPolyLights(std::vector<Vector2> points, float brightness, Color col, PolyLightShader& PLShad, BaseData& bd);
};

#endif