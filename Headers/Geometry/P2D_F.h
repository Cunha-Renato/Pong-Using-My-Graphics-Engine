#pragma once

class P2D_F
{
    public:
        float x = 0.0f;
        float y = 0.0f;

        P2D_F() = default;
        P2D_F(const P2D_F &src_p2d) noexcept;
        P2D_F(const P2D_F &&src_p2d);
        P2D_F(const float &x, const float &y);
        ~P2D_F() {}

        void setPoint(const float &x_, const float &y_)
        {
            this->x = x_;
            this->y = y_;
        }

        P2D_F& operator=(const P2D_F &src_p2d)
        {
            x = src_p2d.x;
            y = src_p2d.y;

            return *this;
        }
};