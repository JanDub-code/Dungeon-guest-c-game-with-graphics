#ifndef RAY_H
#define RAY_H

#include "vectors.h"

class Ray
{
public:
    Ray();
    Ray(Vec2f origin, Vec2f end);
    inline Vec2f getDirection() const
    { return m_end - m_origin; }
    inline Vec2f getCollisionPoint(float time) const
    { return m_origin + getDirection() * time; }
    inline float getDistance() const
    { return getDirection().mag(); }

    Vec2f m_origin;
    Vec2f m_end;
};

#endif // RAY_H
