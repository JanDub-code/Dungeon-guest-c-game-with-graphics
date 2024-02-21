#ifndef __PHYSICAL__
#define __PHYSICAL__

#include "object.h"
#include "hit_circle.h"
#include "aabb.h"

class Entity;
class Player;
class Item;
class Door;

class Physical : public Object
{
protected:
    HitCircle m_hit_circle;
    AABB m_aabb;
    float m_drag;
    float m_friction;
    float m_bounce;
    float m_mass;
    Vec2f m_velocity;
    Vec2f m_prev_velocity;
    Vec2f m_prev_pos;
    bool m_sleeping;
    bool m_is_solid;
public:
    Physical();
    ~Physical();

    enum class ForceMode
    {
        //     Add a continuous force to the phys obj, using its mass.
        Force = 0x0,
        //     Add an instant force impulse to the phys obj, using its mass.
        Impulse = 0x1,
        //     Add an instant velocity change to the phys obj, ignoring its mass.
        VelocityChange = 0x2,
        //     Add a continuous acceleration to the phys obj, ignoring its mass.
        Acceleration = 0x5
    };

    // Returns self as physical
    virtual inline Entity* asEntity() { return nullptr; }
    inline const Entity* asEntity() const { return const_cast<Physical*>(this)->asEntity(); }
    virtual inline Player* asPlayer() { return nullptr; }
    inline const Player* asPlayer() const { return const_cast<Physical*>(this)->asPlayer(); }
    virtual inline Item* asItem() { return nullptr; }
    inline const Item* asItem() const { return const_cast<Physical*>(this)->asItem(); }
    virtual inline Door* asDoor() { return nullptr; }
    inline const Door* asDoor() const { return const_cast<Physical*>(this)->asDoor(); }
    inline Physical* asPhysical() override { return this; }
    void update() override;
    void fixedUpdate() override;
    void addForce(float x, float y, ForceMode forcemode);
    void addForce(Vec2f v, ForceMode forcemode);
    void forceModeForce(Vec2f f);
    void forceModeImpulse(Vec2f f);
    void forceModeVelocity(Vec2f v);
    void forceModeAcceleration(Vec2f a);
    void onCollide(Physical *phys, const Vec2f &push);

    inline void setVelocity(const Vec2f &vel)
    { m_velocity = vel; }
    inline void setPrevVelocity(const Vec2f &prev_vel)
    { m_prev_velocity = prev_vel; }
    inline void setDrag(const float drag)
    { m_drag = drag; }
    inline void setFriction(const float friction)
    { m_friction = friction; }
    inline void setBounce(const float bounce)
    { m_bounce = bounce; }
    inline void setMass(const float mass)
    { m_mass = mass; }
    inline void setPrevPos(const Vec2f &prev_pos)
    { m_prev_pos = prev_pos; }

    inline float getDrag()
    { return m_drag; }
    inline float getFriction()
    { return m_friction; }
    inline float getBounce()
    { return m_bounce; }
    inline float getMass()
    { return m_mass; }
    inline Vec2f getVelocity()
    { return m_velocity; }
    inline Vec2f getPrevVelocity()
    { return m_prev_velocity; }
    inline Vec2f getPrevPos()
    { return m_prev_pos; }
    inline AABB getAABB()
    { return m_aabb; }

    inline bool isAABBColliding(Physical &phys)
    { return m_aabb.isColliding(phys.getAABB()); }
    inline bool isAABBColliding(const AABB &aabb)
    { return m_aabb.isColliding(aabb); }
    inline bool isCircleColliding(Physical &phys)
    { return m_hit_circle.isColliding(phys.m_hit_circle); }

    void sleep();
    void wakeUp();
    inline bool isSleeping()
    { return m_sleeping; }
    void setSolid();
    void setNonSolid();
    inline bool isSolid()
    { return m_is_solid; }

    inline void move(Vec2f dist) override
    {
        m_pos += dist;
        m_aabb.move(dist);
        m_hit_circle.move(dist);
    }

    inline void setPos(Vec2f pos) override
    {
        m_pos = pos;
        m_aabb.setPos(pos);
        m_hit_circle.setPos(pos);
    }

    inline void setPosWithPrevPos(Vec2f pos)
    {
        m_pos = pos;
        m_prev_pos = pos;
        m_aabb.setPos(pos);
        m_hit_circle.setPos(pos);
    }
    //inline AABBCollider getAABBCollider() { return m_aabb; }
};

#endif
