#ifndef POSTPROCESSING
#define POSTPROCESSING
#include "interactiondata.h"

class PostProcessing
{
    InteractionData* m_iData;

    Shader m_shad;
    RenderTexture m_rndrTxtr;
public:
    void init(InteractionData* id);
    void start();
    void end();
};

#endif