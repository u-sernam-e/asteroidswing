#include "waveshader.h"

void WaveShader::init(InteractionData* id)
{
    m_iData = id;

    if (IsRenderTextureReady(m_rndrTxtrA))
        UnloadRenderTexture(m_rndrTxtrA);
    if (IsRenderTextureReady(m_rndrTxtrB))
        UnloadRenderTexture(m_rndrTxtrB);
    if (IsShaderReady(m_comShad))
        UnloadShader(m_comShad);
    if (IsShaderReady(m_drwShad))
        UnloadShader(m_drwShad);


    m_comShad = LoadShader(0, TextFormat("res/shader/%i/wavecompute.fs", GLSLVERSION));
    m_drwShad = LoadShader(0, TextFormat("res/shader/%i/wavedraw.fs", GLSLVERSION));

    m_screenSizeLoc = GetShaderLocation(m_comShad, "screenSize");
    m_frameTimeLoc = GetShaderLocation(m_comShad, "frameTime");
    m_energyLossLoc = GetShaderLocation(m_comShad, "energyLoss");
    m_fluidSquareSizeLoc = GetShaderLocation(m_comShad, "fluidSquareSize");
    m_numDisturbancesLoc = GetShaderLocation(m_comShad, "numDisturbances");

    m_waveDataLoc = GetShaderLocation(m_drwShad, "waveData");
    
	for (int i{}; i < m_disturbancesLoc.size(); ++i)
	{
		m_disturbancesLoc[i] = GetShaderLocation(m_comShad, TextFormat("disturbances[%i]", i));
	}

    Vector2 screenSize(getScreenSize());
    SetShaderValue(m_comShad, m_screenSizeLoc, &screenSize, SHADER_UNIFORM_VEC2);
}

void WaveShader::reset()
{
    m_rndrTxtrA = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    m_rndrTxtrB = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    Image img = GenImageColor(GetScreenWidth(), GetScreenHeight(), {127, 127, 0, 255});
    Texture imgTxtr = LoadTextureFromImage(img);

    BeginTextureMode(m_rndrTxtrA);
    DrawTexture(imgTxtr, 0, 0, WHITE);
    EndTextureMode();

    BeginTextureMode(m_rndrTxtrB);
    DrawTexture(imgTxtr, 0, 0, WHITE);
    EndTextureMode();
}

void WaveShader::updateShaderValues()
{
    float frameTime{lowerLimitFrameTime()};
    SetShaderValue(m_comShad, m_frameTimeLoc, &frameTime, SHADER_UNIFORM_FLOAT);

    float energyLoss{1};
    SetShaderValue(m_comShad, m_energyLossLoc, &energyLoss, SHADER_UNIFORM_FLOAT);

    int fluidSquareSize{17};
    SetShaderValue(m_comShad, m_fluidSquareSizeLoc, &fluidSquareSize, SHADER_UNIFORM_INT);


    int numDisturbances{0};

    if (!m_iData->ship.dead)
    {
        Vector4 shipData{m_iData->ship.pos.x, m_iData->ship.pos.y, 50, 8};
        SetShaderValue(m_comShad, m_disturbancesLoc[numDisturbances], &shipData, SHADER_UNIFORM_VEC4);
        ++numDisturbances;

        if (!m_iData->web.active)
        {
            Vector4 clockData{m_iData->web.clockPos.x, m_iData->web.clockPos.y, -3, 5};
            SetShaderValue(m_comShad, m_disturbancesLoc[numDisturbances], &clockData, SHADER_UNIFORM_VEC4);

            Vector4 counterClockData{m_iData->web.counterClockPos.x, m_iData->web.counterClockPos.y, -3, 5};
            SetShaderValue(m_comShad, m_disturbancesLoc[numDisturbances+1], &counterClockData, SHADER_UNIFORM_VEC4);

            numDisturbances += 2;
        }
    }

    for (auto& a : m_iData->asteroids)
    {
        Vector4 astData{a.pos.x, a.pos.y, 5, a.rad};
        SetShaderValue(m_comShad, m_disturbancesLoc[numDisturbances], &astData, SHADER_UNIFORM_VEC4);
        ++numDisturbances;
    }

    SetShaderValue(m_comShad, m_numDisturbancesLoc, &numDisturbances, SHADER_UNIFORM_INT);
}

void WaveShader::updateTxtr()
{
    updateShaderValues();

    RenderTexture write{m_rndrTxtrA};
    RenderTexture read{m_rndrTxtrB};
    if (m_swapFrame)
    {
        write = m_rndrTxtrB;
        read = m_rndrTxtrA;
    }
    m_swapFrame = !m_swapFrame;

    BeginTextureMode(write);
    BeginShaderMode(m_comShad);

    DrawTextureRec(read.texture, {0, 0, read.texture.width, -read.texture.height}, {0, 0}, WHITE);

    EndShaderMode();
    EndTextureMode();
}

void WaveShader::update()
{
    updateTxtr();
}

void WaveShader::draw()
{
    Texture write{m_rndrTxtrA.texture};
    if (m_swapFrame)
        write = m_rndrTxtrB.texture;

    BeginShaderMode(m_drwShad);
    SetShaderValueTexture(m_drwShad, m_waveDataLoc, write);
    DrawTexture(m_iData->bd.ts.get("res/space.png"), 0, 0, WHITE);
    EndShaderMode();
}