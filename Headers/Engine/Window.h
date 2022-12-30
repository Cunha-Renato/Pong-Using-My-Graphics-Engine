#pragma once

#include <windows.h>
#include "Graphics.h"

class SceneManager;

class Window
{
    private:
        //Variables
        static SceneManager m_SM;
        static WNDCLASSW m_Window_Class;
        static HWND m_Window_Handle;
        static HINSTANCE m_Instance;
        static LPCWSTR m_Name;
        static LPCWSTR m_Title;
        static Graphics *m_Window_Graphics;

        //Private Functions
        static void createWindowObj();
        static void MainLoop();
        static void regWindow();
        static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

    public:
        Window(LPCWSTR class_name, LPCWSTR title);
        ~Window() {};

        static Graphics* getGraphics() {return m_Window_Graphics;}

        static void run();
};