#pragma once

#include "Graphics.h"
#include "SceneManager.h"

class window;

class Scene
{
    protected:
        static SceneManager *m_SM;
        static Window *m_Window;
        static Graphics *m_Graphics;

    public:
        virtual ~Scene(){};
        static void setGraphics(Graphics *gfx);
        static void setWindow(Window *window);
        static void setSceneManager(SceneManager *sm);

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void input(bool wasDown, bool isDown, long keyCode) = 0;
};