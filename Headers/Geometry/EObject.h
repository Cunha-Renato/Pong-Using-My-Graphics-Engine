#pragma once

#include <d2d1.h>
#include <iostream>
#include "P2D_F.h"
#include "..\Engine\Graphics.h"

class EObject
{
    protected:
        bool m_Solid = false; //TODO: Implement
        float m_Center = 0; //TODO: Implement
        P2D_F m_Origin;

        virtual void update() = 0;

    public:
        virtual ~EObject(){};

        //Seters
        virtual void setOrigin(const float &x, const float &y);
        virtual void setOrigin(const P2D_F &src_p2d);
        virtual void setOrigin(P2D_F &&src_p2d);
        virtual void setX(float val);
        virtual void setY(float val);

        //Getters
        P2D_F getOrigin() {return m_Origin;}
        float getXOrigin() {return m_Origin.x;}
        float getYOrigin() {return m_Origin.y;}

        //Angle in degrees
        void move(float angle, float force);

        virtual void draw(Graphics *gfx) = 0;
        virtual bool colided(P2D_F point) = 0; //TODO: Use this to transfer the correct angle for the bouncing;
};