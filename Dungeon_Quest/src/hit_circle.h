#ifndef HIT_CIRCLE_H
#define HIT_CIRCLE_H

#include "vectors.h"

// mostly for combat and item interactions (not suitable for physics collision because there is no Matrix4)
class HitCircle
{
private:
    float m_r;
    Vec2f m_pos;
public:
    HitCircle();
    explicit HitCircle(float r, Vec2f pos) : m_r(r), m_pos(pos) {}
    inline void setPos(const Vec2f &pos)
    { m_pos = pos; }
    inline Vec2f getPos()
    { return m_pos; }
    inline void setRadius(const float r)
    { m_r = r; }
    inline float getRadius()
    { return m_r; }
    inline void move(const Vec2f &dist)
    { m_pos += dist; }
    // circle vs circle
    inline bool isColliding(const HitCircle &hc, const Vec2f shift = Vec2f(0.0F)) const
    {
        if (((hc.m_pos + shift) - m_pos).mag() < (hc.m_r + m_r))
        {
            return true;
        }

        return false;
    }
    // point vs circle
    inline bool isColliding(const Vec2f &pos, const Vec2f shift = Vec2f(0.0F)) const
    {
        if (((pos + shift) - m_pos).mag() < m_r)
        {
            return true;
        }

        return false;
    }
};

#endif // HIT_CIRCLE_H
