#include "menus.h"
#include "button.h"
#include <cmath>

void Menus::init(InteractionData* iData)
{
    m_iData = iData;
    m_iData->bd.ui.addElement<Button>(Button{{50, 300}, {300, 100}, WHITE, LIGHTGRAY, LIGHTGRAY, "Restart?", WHITE, false, false, false, m_iData->bd.ts.get("res/error.png"), false, &m_iData->bd.fs, "res/boleh.ttf"}, "restart");
    m_iData->bd.ui.addElement<Button>(Button{{10, 10}, {70, 70}, WHITE, GRAY, LIGHTGRAY, "", WHITE, false, false, false, m_iData->bd.ts.get("res/pausebutton.png"), true, &m_iData->bd.fs, "res/boleh.ttf"}, "pause");
    m_iData->paused = true;
}

void Menus::reset()
{
    m_iData->shouldRestart = false;
}

void Menus::update()
{
    if (!m_iData->ship.dead && (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_SPACE) || m_iData->bd.ui.getElement<Button>("pause")->pressed()))
        m_iData->paused = !m_iData->paused;
    if (m_iData->ship.dead && (m_iData->bd.ui.getElement<Button>("restart")->pressed() || IsMouseButtonPressed(KEY_R)))
        m_iData->shouldRestart = true;
}

void Menus::draw()
{
    m_iData->bd.ui.getElement<Button>("pause")->setHid(false);
    m_iData->bd.ui.getElement<Button>("restart")->setHid(true);

    if (m_iData->paused)
    {
        DrawTexture(m_iData->bd.ts.get("res/help.png"), 0, 0, WHITE);
    }
    if (m_iData->ship.dead)
    {
        float alpha=std::min(m_iData->bd.gt.timeSince(m_iData->ship.deathTime) * 200, 255.0f);

        m_iData->bd.ui.getElement<Button>("pause")->setHid(true);

        m_iData->bd.ui.getElement<Button>("restart")->setHid(false);
        m_iData->bd.ui.getElement<Button>("restart")->setAlpha(alpha);


        DrawTexture(m_iData->bd.ts.get("res/lose.png"), 0, 0, {255, 255, 255, alpha});
        DrawTextEx(m_iData->bd.fs.get("res/boleh.ttf", 50), TextFormat("Score: %i", m_iData->score.score), {70, 200}, 50, 2, {255, 255, 255, alpha});
    }
}