#include "physical.h"
#include "game_header.h"
#include "dqmath.h"


Physical::Physical()
{
    m_aabb = AABB(m_pos, Vec2f(float(gh::GH_DEFAULT_OBJECT_SIZE)));
    m_hit_circle = HitCircle(1.0F, m_pos);
    m_name = "physical";
    m_velocity = 0.0F;
    m_prev_velocity = 0.0F;
    m_prev_pos = 0.0F;
    m_drag = 0.01F;
    m_friction = 0.01F;
    m_bounce = 1.0F;
    m_mass = 1.0F;
    m_sleeping = false;
    m_is_solid = true;
}

Physical::~Physical()
{
}

void Physical::update()
{
    //emit posChanged();
}

void Physical::fixedUpdate()
{
    if (m_sleeping)
    { return; }
    // TODO: Physics and basic enviromental object behavior (if needed)
    m_prev_pos = m_pos;
    m_prev_velocity = m_velocity;
    m_velocity *= (1.0F - m_drag);
    if (m_velocity.mag() < DQMath::m_fl_zero)
    { m_velocity = 0.0F; }
    move(m_velocity * gh::GH_FIXED_DELTA_TIME);
    emit posChanged();
}

void Physical::addForce(float x, float y, ForceMode forcemode)
{
    addForce(Vec2f(x, y), forcemode);
}

void Physical::addForce(Vec2f v, ForceMode forcemode)
{
    switch (forcemode)
    {
    case ForceMode::Force:
        // Push
        forceModeForce(v);
        break;
    case ForceMode::Impulse:
        forceModeImpulse(v);
        break;
    case ForceMode::VelocityChange:
        forceModeVelocity(v);
        break;
    case ForceMode::Acceleration:
        forceModeAcceleration(v);
        break;
    default:
        break;
    }
}

void Physical::forceModeForce(Vec2f f)
{
    float temp_mass = m_mass;

    if (!m_mass)
    {
        temp_mass = 0.0000001F;
    }

    Vec2f acc = f / temp_mass;
    m_velocity += acc * gh::GH_FIXED_DELTA_TIME;
    //m_velocity = m_prev_velocity + acc * gh::GH_FIXED_DELTA_TIME;
}

void Physical::forceModeImpulse(Vec2f f)
{
    float temp_mass = m_mass;

    if (!m_mass)
    {
        temp_mass = 0.0000001F;
    }

    m_velocity = (f * gh::GH_FIXED_DELTA_TIME + m_velocity * temp_mass) / temp_mass;
}

void Physical::forceModeVelocity(Vec2f v)
{
    m_velocity += v * gh::GH_FIXED_DELTA_TIME;
}

void Physical::forceModeAcceleration(Vec2f a)
{

}

void Physical::onCollide(Physical *phys, const Vec2f &push)
{
    if (m_sleeping)
    {
        //phys->move(push.negated());
        return;
    }

    //Vec2f temp_pudh = push / 2.0F;
    //phys->move(temp_pudh.negated());
#if 0
    Vec2f ext_momentum = phys->m_velocity * phys->m_mass;
    Vec2f rel_vel = m_velocity - ext_momentum;
    rel_vel *= (1.0F - m_friction);
#else
    //move(temp_pudh);
    move(push);

    //m_velocity += phys->getVelocity().getAbs() * push.negated();

    if (push.mag() < DQMath::m_fl_zero * 1.0F) // 1.0F is scale
    {
        return;
    }

    const Vec2f push_proj = push * (m_velocity.dot(push) / push.dot(push));
    m_velocity = (m_velocity - push_proj) * (1.0f - m_friction) - push_proj * m_bounce;
#endif
}

void Physical::sleep()
{
    m_sleeping = true;
}

void Physical::wakeUp()
{
    m_sleeping = false;
}

void Physical::setSolid()
{
    m_is_solid = true;
}

void Physical::setNonSolid()
{
    m_is_solid = false;
}
