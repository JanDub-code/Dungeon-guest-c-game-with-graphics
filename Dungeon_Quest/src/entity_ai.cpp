#include "entity_ai.h"
#include "ray.h"
#include "entity.h"
#include "dqmath.h"
#include "Time.h"
#include "game_header.h"

#define PHYSICS_ENABLED

EntityAI::EntityAI()
{
    m_is_enabled = false;
    m_attack_enabled = false;
    m_move_speed = 1.0F;
    m_distance_visibility = 4.0F;
    m_distance_min = 0.0F;
    m_attack_cooldown = 1.0F;
    m_attack_period = m_attack_cooldown;
}

EntityAI::~EntityAI()
{
}

void EntityAI::followObject(/*AABB aabb, */Entity *source, Object *dest)
{
    if (!m_is_enabled)
    { return; }

    Ray ray(source->getPos(), dest->getPos());
    if (ray.getDistance() > m_distance_visibility)
    { return; }
    if (ray.getDistance() < DQMath::m_fl_zero)
    { return; }
    if (ray.getDistance() < m_distance_min)
    { return; }
#if 0
    // TODO: aabb calculate collision point with ray
    ray.getCollisionPoint(time from 0 to 1);
#endif

#ifdef PHYSICS_ENABLED
    Vec2f temp_vel = source->getVelocity() + ray.getDirection().normalized() * m_move_speed * gh::GH_FIXED_DELTA_TIME;

    if (temp_vel.mag() > m_move_speed)
    {
        temp_vel.normalize();
        temp_vel *= m_move_speed;
    }

    source->setVelocity(temp_vel);
#else
    source->m_velocity = ray.getDirection().normalized() * m_move_speed;
#endif
}

void EntityAI::randomMovement(Entity *source)
{
    // TODO: Make monster move in random directions
}

void EntityAI::setMovementSpeed(float speed)
{
    m_move_speed = speed;
}

void EntityAI::setDistanceVisibility(float dist)
{
    m_distance_visibility = dist;
}

void EntityAI::setAttackCooldown(float cooldown)
{
    m_attack_cooldown = cooldown;
}

void EntityAI::setMinFollowDistance(float dist)
{
    m_distance_min = dist;
}

void EntityAI::setAttackEnabled()
{
    m_attack_enabled = true;
}

void EntityAI::setAttackDisabled()
{
    m_attack_enabled = false;
}

void EntityAI::actionAttack(Entity *source, Entity *target)
{
    if (!m_is_enabled)
    { return; }
    if (!m_attack_enabled)
    { return; }

    m_attack_period -= gh::GH_FIXED_DELTA_TIME;

    if (m_attack_period <= 0.0F)
    {
        m_attack_period = m_attack_cooldown;
        source->actionAttack(target);
    }
}

void EntityAI::setDisabled()
{
    m_is_enabled = false;
}

void EntityAI::setEnabled()
{
    m_is_enabled = true;
}

bool EntityAI::isEnabled()
{
    return m_is_enabled;
}
