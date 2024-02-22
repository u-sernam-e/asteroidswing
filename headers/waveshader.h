#ifndef WAVESHADER
#define WAVESHADER
#include "interactiondata.h"
#include <array>

class WaveShader : public Ob
{
    InteractionData* m_iData;

    Shader m_comShad;
    RenderTexture m_rndrTxtrA;
    RenderTexture m_rndrTxtrB;
    bool m_swapFrame; // this swaps between true and false every frame, and swaps which rendertxtr is the read and which is the write
                      // it has to do this because if it doesn't, then a weird diagonal artifact appears on the screen

    unsigned int m_screenSizeLoc; // these are all for comshad
    unsigned int m_frameTimeLoc;
    unsigned int m_energyLossLoc;
    unsigned int m_fluidSquareSizeLoc;
    std::array<unsigned int, 10> m_disturbancesLoc;
    unsigned int m_numDisturbancesLoc;
    
    Shader m_drwShad;

    unsigned int m_waveDataLoc;

    void updateShaderValues();
    void updateTxtr();
public:
    void init(InteractionData* id);
    void reset();
    void update() override;
    void draw() override;

    ~WaveShader()
    {
        UnloadRenderTexture(m_rndrTxtrA);
        UnloadRenderTexture(m_rndrTxtrB);
        UnloadShader(m_comShad);
        UnloadShader(m_drwShad);
    }
};

#endif