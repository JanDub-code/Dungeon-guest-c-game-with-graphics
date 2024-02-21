#include "dqmath.h"
#include "tile.h"
#include "ray.h"
#include "aabb.h"
#include "physical.h"

const float DQMath::m_fl_zero = 1E-8F;

DQMath::DQMath()
{

}

DQMath::~DQMath()
{

}

#include <iostream>
std::vector<std::vector<Tile*>> DQMath::convertTileVecTo2DMat(const std::vector<Tile*> tiles, const Vec2i &size)
{
    std::cout << "Tile vec to tile mat convertor:\nNumber of tiles: "
              << tiles.size()
              << "\nMap dimensions:\nX: " << size.x
              << "\nY: " << size.y << std::endl;

    std::vector<std::vector<Tile*>> tile_mat;

    if (int(tiles.size()) == size.x * size.y)
    {
        for (int y = 0; y < size.y; y++)
        {
            std::vector<Tile*> line;

            for (int x = 0; x < size.x; x++)
            {
                line.push_back(tiles.at(DQMath::xyToVec1(x, y, size.x)));
                //obj->m_aabb.move(x, y);
            }

            tile_mat.push_back(line);
        }
    }
    else
    {
        // TODO: Implement crash handler (no GS_LAST)
        //*m_gamestate = GameState::GS_LAST;
    }

    return tile_mat;
}
#include <iostream>
bool DQMath::rayVsRectCollision(const Ray &ray, const AABB &expanded, Vec2f &contact_point, Vec2f &contact_normal, float &hit_near)
{
    contact_normal = 0.0F;
    contact_point = 0.0F;

    const Vec2f ray_inv_dir = ray.m_end.inverted();

    Vec2f near = (expanded.getPos() - ray.m_origin) * ray_inv_dir;
    Vec2f far = (expanded.getPos() + expanded.getSize() - ray.m_origin) * ray_inv_dir;

    if (std::isnan(far.y) || std::isnan(far.x)) return false;
    if (std::isnan(near.y) || std::isnan(near.x)) return false;
    // Sort distances
    if (near.x > far.x) std::swap(near.x, far.x);
    if (near.y > far.y) std::swap(near.y, far.y);

    // Early rejection
    if (near.x > far.y || near.y > far.x) return false;

    // Closest 'time' will be the first contact
    hit_near = std::max(near.x, near.y);

    // Furthest 'time' is contact on opposite side of target
    float t_hit_far = std::min(far.x, far.y);

    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0)
    {
        return false;
    }

    // Contact point of collision from parametric line equation
    contact_point = ray.m_origin + ray.m_end * hit_near;

    if (near.x > near.y)
    {
        if (ray_inv_dir.x < 0)
        {
            contact_normal = Vec2f(1.0F, 0.0F);
        }
        else
        {
            contact_normal = Vec2f(-1.0F, 0.0F);
        }
    }
    else if (near.x < near.y)
    {
        if (ray_inv_dir.y < 0)
        {
            contact_normal = Vec2f(0.0F, 1.0F);
        }
        else
        {
            contact_normal = Vec2f(0.0F, -1.0F);
        }
    }

    std::cout << "collided tile rayVsRectCollision!" << std::endl;
    return true;
}

bool DQMath::aabbDynamicCollision( Physical *phys_dynamic, const AABB &aabb_static,Vec2f &contact_point,
                                  Vec2f &contact_normal, float &hit_near)
{
    if (phys_dynamic->getVelocity().x == 0.0F && phys_dynamic->getVelocity().y == 0.0F)
    {
        return false;
        //return aabb_static.isColliding(phys_dynamic->getAABB());
    }

    const AABB expanded(aabb_static.getPos() - (phys_dynamic->getAABB().getSize() * 0.5F), aabb_static.getSize() + (phys_dynamic->getAABB().getSize()));
    const Ray ray(phys_dynamic->getPrevPos() + (phys_dynamic->getAABB().getSize() * 0.5F), phys_dynamic->getPos());

    if (rayVsRectCollision(ray, expanded, contact_point, contact_normal, hit_near))
    {
        std::cout << "collided tile aabbDynamicCollision!\nCN:\nX: " << contact_normal.x << "\nY: " << contact_normal.y << "\nCP: " << std::endl;
        return hit_near >= 0.0F && hit_near < 1.0F;
    }

    return false;
}

// INFO: First is aabb input because tiles are not Physical objects (for some reason)
Vec2f DQMath::resolveStaticVsPhysicalCollision(Physical *phys_dynamic, const AABB &aabb_static)
{
    Vec2f contact_point;
    Vec2f contact_normal;
    float contact_near = 0.0F;

    if (aabbDynamicCollision(phys_dynamic, aabb_static, contact_point, contact_normal, contact_near))
    {
        std::cout << "collided tile resolveStaticVsPhysicalCollision!" << std::endl;
        return contact_normal * Vec2f(std::abs(phys_dynamic->getVelocity().x), std::abs(phys_dynamic->getVelocity().y)) * (1.0F - contact_near);
    }

    return Vec2f(0.0F);
}
// INFO: This game is not chunk-based so there is always single chunk only (chunk => scene map size)
std::vector<int> DQMath::cropSurroundings(size_t chunk, size_t width, size_t height, const Vec2f &pos, const Vec2f &borders, float tile_size)
{
    if (chunk != width * height)
    {
        return std::vector<int>();
    }

    int x_start = int(std::floor(pos.x - borders.x));
    int y_start = int(std::floor(pos.y - borders.y));
    int x_end = int(std::ceil(pos.x + borders.x + tile_size));
    int y_end = int(std::ceil(pos.y + borders.y + tile_size));
    std::vector<int> crop;

    if (x_start < 0)
    { x_start = 0; }

    if (y_start < 0)
    { y_start = 0; }

    if (x_end >= static_cast<int>(width))
    { x_end = static_cast<int>(width); }

    if (y_end >= static_cast<int>(height))
    { y_end = static_cast<int>(height); }

    for (int y = y_start; y < y_end; y++)
    {
        for (int x = x_start; x < x_end; x++)
        {
            crop.push_back(xyToVec1(x, y, static_cast<int>(width)));
        }
    }

    return crop;
}
