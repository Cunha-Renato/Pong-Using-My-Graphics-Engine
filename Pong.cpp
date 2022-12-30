#include "Pong.h"

#define DEBUG 0
#if DEBUG == 1

#include <iostream>
#include <string>
#include <sstream>
#define LOGSTR(x) std::cout<<(x)<<std::endl

#else
#define LOGSTR(x)
#endif

Pong::Pong() : Scene::Scene() {}

Pong::~Pong(){}

void Pong::init()
{
    m_Canvas.setRect(m_Graphics->getRect()); 
    m_Player[0].setRect(60, (m_Canvas.getHeight()/2 - 80.0f), 15.0f, 160.0f);
    m_Player[1].setRect((m_Canvas.getWidth() - 60), (m_Canvas.getHeight()/2 - 80.0f), 15.0f, 160.0f);

    m_Ball.setEEllipse(m_Canvas.getWidth()/2, m_Canvas.getHeight()/2, 15, 15);
}

void Pong::ballColision()
{
    float ballX = m_Ball.getOrigin().x;
    float ballY = m_Ball.getOrigin().y;

    //Colision with the walls
    //
    if(ballY + m_Ball.getEllipse().radiusY >= m_Canvas.getHeight() || ballY - m_Ball.getEllipse().radiusY <= m_Canvas.getOrigin().y)
        m_Speed_Y *= -1; 
    
    else if(ballX - m_Ball.getEllipse().radiusX <= m_Canvas.getOrigin().x || ballX + m_Ball.getEllipse().radiusX >= m_Canvas.getWidth())
    {
        if(m_Speed_X < 0)
            m_Score_Points[0]++;
        else
            m_Score_Points[1]++;

        m_Speed_Y = 10;
        m_Speed_X *= -1;
        init();
    }

    P2D_F point(m_Ball.getXOrigin() - m_Ball.getRadius() +5, m_Ball.getYOrigin() - m_Ball.getRadius()); 
    if(m_Player[0].colided(point))
    {
        m_Ball.setOrigin(m_Ball.getXOrigin() + m_Ball.getRadius(), m_Ball.getYOrigin());
        m_Speed_X *= -1;
        
        m_Speed_Y = (m_Speed_Y > 0) ? 10.0f : -10.0f;

        if(m_Move[0])
        {
            if(!m_MoveUp[0])
                m_Speed_Y += 5;
        
            else
                m_Speed_Y -= 5;
        }
    }

    point.setPoint(m_Ball.getXOrigin() + m_Ball.getRadius() -5, m_Ball.getYOrigin() - m_Ball.getRadius()); 
    if(m_Player[1].colided(point))
    {
        m_Ball.setOrigin(m_Ball.getXOrigin() - m_Ball.getRadius(), m_Ball.getYOrigin());
        m_Speed_X *= -1;

        m_Speed_Y = (m_Speed_Y >= 0) ? 10.0f : -10.0f;
    
        if(m_Move[1])
        {
            if(!m_MoveUp[1])
                m_Speed_Y += 5;
        
            else
                m_Speed_Y -= 5;
        }
    }
}

void Pong::update() 
{
    for(int i=0; i<2; i++)
    {
        if(m_Move[i])
        {
            if(m_MoveUp[i])
                m_Player[i].move(90, m_Player_Speed[i]);
            else if(!m_MoveUp[i])
                m_Player[i].move(270, m_Player_Speed[i]);

            if(m_Player[i].getRect().top <= m_Canvas.getRect().top)
                m_Player[i].setOrigin(m_Player[i].getXOrigin(), m_Canvas.getRect().top);    
                
            else if(m_Player[i].getRect().bottom >= m_Canvas.getRect().bottom)
                m_Player[i].setOrigin(m_Player[i].getXOrigin(), m_Canvas.getRect().bottom - m_Player[i].getHeight());

            // LOGSTR(m_Move[i]);
        }
    }

    m_Ball.setOrigin(m_Ball.getXOrigin() - m_Speed_X, m_Ball.getYOrigin() + m_Speed_Y);
    ballColision();

    // std::cout << m_Score_Points[0] << " - " << m_Score_Points[1] << std::endl;

    for(int i=0; i<2; i++)
        if(m_Score_Points[i] >= 10) 
        {
            m_SM->setActiveScene(1);
            break;
        }
}

void Pong::render() 
{
    m_Graphics->beginDraw();

    m_Graphics->paintBackground(0.20f, 0.20f, 0.20f);
    m_Player[0].draw(m_Graphics);
    m_Player[1].draw(m_Graphics);
    m_Ball.draw(m_Graphics);


    //Middle Line

    float aux = m_Canvas.getHeight()/15.0f;
    Rect re[2];
    re[0].setRect(m_Canvas.getWidth()/2 - 3, 0, 6, aux);

    aux /= 5;
    for(int i=0; i<15; i++)
    {
        m_Graphics->fillRect(re[0].getRect());
        
        re[0].setY(re[0].getYOrigin() + re[0].getHeight() + aux);
    }

    //Socre Points

    aux = m_Canvas.getHeight()/10.0f;
    re[0].setRect(0, 0, 8, aux-5);
    re[1].setRect(m_Canvas.getWidth() - 8, 0, 8, aux-5);

    for(int i=0; i<2; i++)
        for(int j=0; j<m_Score_Points[i]; j++)
        {
            m_Graphics->fillRect(re[i].getRect());
            re[i].setY(re[i].getYOrigin() + re[i].getHeight() + 5);
        }
    

    m_Graphics->endDraw();
}

void Pong::input(bool wasDown, bool isDown, long keyCode)
{
    if(keyCode == 'W' || keyCode == 'S' || keyCode == VK_UP || keyCode == VK_DOWN || keyCode == VK_RIGHT || keyCode == VK_SPACE)
    {
        if(isDown)
        {
            if(keyCode == 'W')
            {
                m_Move[0] = true;
                m_MoveUp[0] = true;
            }
            else if(keyCode == 'S')
            {
                m_Move[0] = true;
                m_MoveUp[0] = false;
            }

            if(keyCode == VK_UP)
            {
                m_Move[1] = true;
                m_MoveUp[1] = true;

                LOGSTR("UP pressed");
            }
            else if(keyCode == VK_DOWN)
            {
                m_Move[1] = true;
                m_MoveUp[1] = false;
            }

            if(keyCode == VK_SPACE)
                m_Player_Speed[0] = 20;

            if(keyCode == VK_RIGHT)
                m_Player_Speed[1] = 20;
        }
        else if(keyCode != VK_SPACE && keyCode != VK_RIGHT)
        {
            if(keyCode == 'W' || keyCode == 'S')
                m_Move[0] = false;
                
            else m_Move[1] = false;
        }
        else
        {
            if(keyCode == VK_SPACE)
                m_Player_Speed[0] = 10;
    
            else m_Player_Speed[1] = 10;
        }
    }
}