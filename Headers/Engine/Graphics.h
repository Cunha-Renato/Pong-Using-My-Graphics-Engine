#pragma once

#include <windows.h>
#include <d2d1.h>

class Graphics
{
    private:
        ID2D1Factory *m_Factory;
        ID2D1HwndRenderTarget *m_Render_Target = nullptr; 
        ID2D1SolidColorBrush *m_Brush = nullptr;

        RECT m_Rect = {0};

    public:
        Graphics() = default;
        Graphics(HWND window_handle);
        ~Graphics();

        bool init(HWND window_handle);

        RECT getRect() {return m_Rect;}

        void drawLine(float x1, float y1, float x2, float y2);
        void fillRect(const D2D1_RECT_F *const rect);
        void fillRect(const D2D1_RECT_F &&rect);
        void fillEllipse(const D2D1_ELLIPSE *const ellipse);
        void paintBackground(float r, float g, float b);
        void beginDraw() {m_Render_Target->BeginDraw();}
        void endDraw() {m_Render_Target->EndDraw();}
};