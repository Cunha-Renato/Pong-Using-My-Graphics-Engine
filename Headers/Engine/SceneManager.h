#pragma once

#include <iostream>
#include <vector>

class Window;
class Scene;

class SceneManager
{
    private:
        static int m_Active_Scene_Index;
        static Window *m_Window;
        static std::vector<Scene*> m_Scenes;

    public:
        SceneManager() {};
        SceneManager(Window *window);
        SceneManager(Window *window, std::vector<Scene*> scenes);
        ~SceneManager() {}   

        void add(Scene *scene);
        void remove(int index);

        static void setActiveScene(Scene *scene);
        static void setActiveScene(int index);
        static void initScene();
        static void runInput(bool wasDown, bool isDown, long keyCode);
        static void runScene();
        
        static const std::vector<Scene*> getScenes() {return m_Scenes;}
};