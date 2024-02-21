#ifndef AABB_H
#define AABB_H

#include "vectors.h"
#include <vector>

class AABB
{
private:
    // TODO: Change to min max (min_x, max_x, min_y, max_y and add function move to have resizable colliders)
    Vec2f m_pos;
    Vec2f m_size;
public:
    AABB();
    AABB(const Vec2f &pos, const Vec2f &size);

    inline void setPos(const Vec2f &pos)
    { m_pos = pos; }
    inline void setSize(const Vec2f &size)
    { m_size = size; }
    inline Vec2f getPos() const
    { return m_pos; }
    inline Vec2f getSize() const
    { return m_size; }
    inline void move(const Vec2f &dist)
    {m_pos += dist; }

    inline bool isColliding(const AABB aabb) const
    {
        return aabb.m_pos.x + aabb.m_size.x > m_pos.x &&
               aabb.m_pos.x < m_pos.x + m_size.x ?
              (aabb.m_pos.y + aabb.m_size.y > m_pos.y &&
               aabb.m_pos.y < m_pos.y + m_size.y) : false;
    }

    inline bool isPointColliding(const Vec2f point) const
    {
        return point.x > m_pos.x &&
               point.x < m_pos.x + m_size.x ?
              (point.y > m_pos.y &&
               point.y < m_pos.y + m_size.y) : false;
    }

    bool calcDynamicCollision(const AABB aabb, Vec2f prev_pos, Vec2f& contact_point, Vec2f &contact_normal, float &hit_near, float &hit_far);
    inline Vec2f getCenter() const
    { return m_pos + (m_size * 0.5F); }
};

#endif // AABB_H
