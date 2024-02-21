#ifndef ENTITY_AI_H
#define ENTITY_AI_H

#include "object.h"
#include "aabb.h"

class Entity;

class EntityAI
{
private:
    float m_is_enabled;
    float m_attack_enabled;
    float m_move_speed;
    float m_distance_visibility;
    float m_distance_min;
    float m_attack_cooldown;
    float m_attack_period;
public:
    EntityAI();
    ~EntityAI();
    void followObject(/*AABB aabb, */Entity *source, Object *dest);
    void randomMovement(Entity *source);
    void setMovementSpeed(float speed);
    void setDistanceVisibility(float dist);
    void setAttackCooldown(float cooldown);
    void setMinFollowDistance(float dist);
    void setAttackEnabled();
    void setAttackDisabled();
    void actionAttack(Entity *source, Entity *target);
    void setDisabled();
    void setEnabled();
    bool isEnabled();
};

#endif // ENTITY_AI_H

// INFO: Rushed because not enough time... so no path finding, no nav-nodes
