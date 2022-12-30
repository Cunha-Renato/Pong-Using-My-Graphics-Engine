#pragma once

#include "EObject.h"
#include <d2d1.h>

//TODO: Finish implementing the calculation for the center
class Rect : public EObject
{
    private:
        float m_Width = 0;
        float m_Height = 0;
        D2D1_RECT_F *m_Rect = new D2D1_RECT_F;

        void update();

    public:
        Rect() : EObject(){};
        Rect(const Rect &src_rect) noexcept;
        Rect(Rect &&src_rect);

        //Will set de provided pointer to nullptr
        Rect(D2D1_RECT_F *src_rect);
        Rect(const D2D1_RECT_F &src_rect);
        Rect(const D2D1_RECT_F &&src_rect);

        Rect(float x, float y, float width, float height);
        Rect(const P2D_F &src_p2d, float width, float height);
        Rect(const P2D_F &&src_p2d, float width, float height);
        ~Rect();

        Rect& operator=(const Rect &src_rect)
        {
            m_Origin = src_rect.m_Origin;
            *m_Rect = *src_rect.m_Rect;

            return *this;
        }
        Rect& operator=(Rect &&src_rect)
        {
            if(&src_rect == this) return *this; 

            m_Origin = std::move(src_rect.m_Origin);
            m_Rect = std::move(src_rect.m_Rect);

            src_rect.m_Rect = nullptr;

            return *this;
        }   

        //Seters
        //TODO: Do all the other setters, but not now
        void setRect(float x, float y, float width, float height);
        void setRect(const RECT &src_rect);

        //Geters
        float getHeight() {return m_Height;}
        float getWidth() {return m_Width;}
        const D2D1_RECT_F getRect() {return *m_Rect;}

        void draw(Graphics *gfx);

        bool colided(P2D_F point);
};