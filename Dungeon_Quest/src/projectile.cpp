#include "projectile.h"
#include "game_header.h"

Projectile::Projectile(Vec2f init_pos, float dist_lim)
{
    m_name = "projectile";
    m_owner = "default";
    m_pos = init_pos;
    m_init_pos = init_pos;
    m_dist_lim = dist_lim;
    m_visual_size = Vec2i(gh::GH_DEFAULT_PROJECTILE_VISUAL_SIZE);
    m_aabb = AABB(m_pos, Vec2f(gh::GH_DEFAULT_PROJECTILE_SIZE));
    m_strength = 4;
    //m_ray.m_end = m_pos;
}

Projectile::~Projectile()
{

}

bool Projectile::hasReachedEnd()
{
    return (m_pos - m_init_pos).mag() > m_dist_lim;
}

void Projectile::setDynamicVelocity(Vec2f vel)
{
    m_velocity = vel * gh::GH_DEFAULT_PROJECTILE_SPD_MUL;
}

void Projectile::setOwner(std::string owner)
{
    m_owner = owner;
}

std::string Projectile::getOwner()
{
    return m_owner;
}
