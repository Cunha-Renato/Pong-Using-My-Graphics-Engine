#include <iostream>

#include "Headers\Engine.h"
#include "Headers\Geometry.h"
#include "Pong.h"
#include "EndScene.h"


int main()
{
    Window window(L"Pong", L"Pong");

    SceneManager sm(&window);
    Pong pong;
    EndScene es;

    sm.add(&pong);
    sm.add(&es);
    sm.setActiveScene(&pong);
    sm.initScene();

    window.run();
    return 0;
}