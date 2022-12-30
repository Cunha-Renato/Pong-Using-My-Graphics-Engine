#include "EndScene.h"
#include "Pong.h"

void EndScene::init()
{
    int *scores = ((Pong*)(m_SM->getScenes().at(0)))->getScores();
    
    m_Winner = (scores[0] >= scores[1]) ? 0 : 1;

    Rect canvas;
    canvas.setRect(m_Graphics->getRect());

    m_Rect.setRect(canvas.getWidth()/2 - 35, canvas.getHeight()/2 - 150, 70, 300);
}

void EndScene::render()
{
    m_Graphics->beginDraw();
    m_Graphics->paintBackground(0.20f, 0.20f, 0.20f);

    if(m_Winner)
    {
        Rect canvas;
        canvas.setRect(m_Graphics->getRect());

        float xPos = canvas.getWidth()/2 - 35;

        for(int i=0; i<2; i++)
        {
            m_Rect.setX(xPos - 70.0f + (i*150.0f));
            m_Rect.draw(m_Graphics);
        }
    }

    m_Rect.draw(m_Graphics);

    m_Graphics->endDraw();
}