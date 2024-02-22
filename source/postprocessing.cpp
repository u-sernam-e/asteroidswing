#include "postprocessing.h"

void PostProcessing::init(InteractionData* id)
{
    m_iData = id;

    m_rndrTxtr = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    //m_shad = LoadShader(0, "res/shader/330/bloom.fs");
}

void PostProcessing::start()
{
    BeginTextureMode(m_rndrTxtr);
}

void PostProcessing::end()
{
    EndTextureMode();
    BeginShaderMode(m_shad);
    DrawTextureRec(m_rndrTxtr.texture, {0, 0, m_rndrTxtr.texture.width, -m_rndrTxtr.texture.height}, {0, 0}, WHITE);
    EndShaderMode();
}