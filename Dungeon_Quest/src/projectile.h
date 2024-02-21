#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"
//#include "ray.h"

class Projectile : public Entity
{
    Q_OBJECT
private:
    //Ray m_ray;
    Vec2f m_init_pos; // TODO: Projectile will have lifespan based on distance traveled (don't forget to set velocity)
    float m_dist_lim;
    std::string m_owner;
public:
    Projectile(Vec2f init_pos, float dist_lim);
    ~Projectile();
    Projectile* asProjectile() override { return this; }
    bool hasReachedEnd();
    void setDynamicVelocity(Vec2f vel);
    void setOwner(std::string owner);
    std::string getOwner();
};

#endif // PROJECTILE_H
