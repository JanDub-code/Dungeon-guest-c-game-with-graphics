#include "aabb.h"
#include "ray.h"

AABB::AABB()
{
    m_pos = Vec2f(0.0F);
    m_size = Vec2f(1.0F);
}

AABB::AABB(const Vec2f &pos, const Vec2f &size)
{
    m_pos = pos;
    m_size = size;
}

// TODO: Fix bug when aabb is directly touching other's aabb border
bool AABB::calcDynamicCollision(const AABB aabb, Vec2f prev_pos, Vec2f &contact_point, Vec2f &contact_normal, float &hit_near, float &hit_far)
{
    contact_point = 0.0F;
    contact_normal = 0.0F;
    hit_near = 0.0F;
    hit_far = 0.0F;
    Ray ray;
    ray.m_origin = prev_pos;// + aabb.m_size * 0.5F;
    ray.m_end = aabb.m_pos;
    const Vec2f ray_dir = ray.getDirection();

    Vec2f expanded_pos = m_pos - (aabb.m_size * 0.5F);
    Vec2f expanded_size = m_size + (aabb.m_size * 0.5F);

    // These are percentages. 0 means at physical's first position and 100 means at physical's current position
    Vec2f near = (expanded_pos - ray.m_origin) / ray_dir;
    Vec2f far = (expanded_pos + expanded_size - ray.m_origin) / ray_dir;

    if (near.x > far.x)
    {
        std::swap(near.x, far.x);
    }

    if (near.y > far.y)
    {
        std::swap(near.y, far.y);
    }

    if (near.x > far.y || near.y > far.x)
    {
        return false;
    }

    hit_near = std::max(near.x, near.y);
    hit_far = std::min(far.x, far.y);

    if (hit_far < 0.0F)
    {
        return false;
    }

    if (hit_near > 1.0F)
    {
        return false;
    }

    contact_point = ray.getCollisionPoint(hit_near);
    //Vec2f contact_point_end = ray.getCollisionPoint(1.0F);
    //Vec2f contact_normal(0.0F);

    if (near.x > near.y)
    {
        if (ray_dir.x < 0.0F)
        {
            contact_normal += Vec2f(1.0F, 0.0F);

        }
        else
        {
            contact_normal += Vec2f(-1.0F, 0.0F);
        }
    }
    else if (near.x < near.y)
    {
        if (ray_dir.y < 0.0F)
        {
            contact_normal += Vec2f(0.0F, 1.0F);
        }
        else
        {
            contact_normal += Vec2f(0.0F, -1.0F);
        }
    }

    return true;
}
