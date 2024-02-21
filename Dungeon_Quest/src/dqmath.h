#ifndef DQMATH_H
#define DQMATH_H

#include <vector>
#include "vectors.h"

class Tile;
class AABB;
class Physical;
class Ray;

class DQMath
{
private:
    DQMath();
    ~DQMath();
public:
    static inline int xyToVec1(int x, int y, int row_len)
    { return ((row_len * y) + x); }
    // Converts X Y coordinates to a single number based on the row length
    static inline float lerp(float d, float min, float max)
    { return min + d * (max - min); }
    static std::vector<std::vector<Tile*>> convertTileVecTo2DMat(const std::vector<Tile*> tiles, const Vec2i &size);
    static inline float rot(float max, float val)
    { return val / max * 100.0F; }

    static bool rayVsRectCollision(const Ray &ray, const AABB &expanded, Vec2f &contact_point, Vec2f &contact_normal, float &hit_near);
    static bool aabbDynamicCollision(Physical *phys_dynamic, const AABB &aabb_static, Vec2f &contact_point,
                                     Vec2f &contact_normal, float &hit_near);
    static Vec2f resolveStaticVsPhysicalCollision(Physical *phys_dynamic, const AABB &aabb_static);
    static std::vector<int> cropSurroundings(size_t chunk, size_t width, size_t height, const Vec2f &pos, const Vec2f &borders, float tile_size);

    static const float m_fl_zero;
};

#endif // DQMATH_H
