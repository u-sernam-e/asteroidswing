#ifndef BASEDATA
#define BASEDATA 
#include "texturestorage.h"
#include "soundstorage.h"
#include "fontstorage.h"
#include "musicstorage.h"
#include "uimaster.h"
#include "timer.h"

// this class can be used by classes to access different base datas

struct BaseData
{
    UiScene ui;
    TextureStorage ts;
    FontStorage fs;
    SoundStorage ss;
    MusicStorage ms;
    Timer gt; // global timer
};

void initBD(BaseData& b);
void updateBD(BaseData& b);
void drawBD(BaseData& b);


// also this is here
#define GLSLVERSION 330
#if defined(PLATFORM_WEB)
    #define GLSLVERSION 100
#endif

#endif