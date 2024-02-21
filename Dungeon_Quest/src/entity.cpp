#include "entity.h"
#include "game_header.h"
#include "projectile.h"
#include "weapon.h"
#include "melee.h"

Entity::Entity()
{
    m_name = "entity";
    m_health = 1;
    m_health_max = m_health;
    m_strength = 1;
    m_protection = 0;
    m_holding_item = nullptr;
    m_projectile = nullptr;
    //m_armor = nullptr;
    m_sound.setAudioOutput(&m_aud_out);
    // m_sound.setSource(QUrl("qrc:/src/assets/sounds/hurt1.mp3")); // INFO: default none
    m_onclickfunct = nullptr;
}

Entity::~Entity()
{
    if (m_holding_item)
    {
        delete m_holding_item;
    }
}

void Entity::update()
{

}

void Entity::setHealth(int health)
{
    m_health = health;

    if (m_health > m_health_max)
    {
        m_health_max = m_health;
        emit healthMaxChanged();
    }

    emit healthChanged();
}

int Entity::getHealth()
{
    return m_health;
}

int Entity::getHealthMax()
{
    return m_health_max;
}

void Entity::addHealth(int ammount)
{
    if (m_health += ammount <= m_health_max)
    {
        m_health += ammount;
        emit healthChanged();
    }
}

// Entiti to be attacked
void Entity::actionAttack(Entity *entity)
{
    m_aud_out.setVolume(gh::GH_ENTITY_VOLUME);
    m_sound.setPosition(0);
    m_sound.play();

    if (m_holding_item)
    {
        Weapon *weapon = m_holding_item->asWeapon();

        if (weapon)
        {
            Melee *melee = weapon->asMelee();

            if (melee) // INFO: Rushed solution (no sword but melee as parent for non-implemented sword)
            {
                entity->actionGetAttacked(-(m_strength + melee->getHarmAmmount()));
                return;
            }
        }
    }
#if 0
    Sword *sword = m_holding_item.asSword();
    // TODO: add asSword() function directly to class Item instead of class Object.
    //       (because holding item will always be Item and not Object)

    if (sword)
    {
        entity->actionGetHit(-(m_strength + sword->getSharpness()));
        return;
    }
#endif
    entity->actionGetAttacked(-m_strength);
    //emit entity->healthChanged();
}

void Entity::actionGetAttacked(int ammount)
{
    m_aud_out.setVolume(gh::GH_ENTITY_VOLUME);
    m_sound.setPosition(0);
    m_sound.play();
    m_health += ammount;
    emit healthChanged();
}

void Entity::setHoldingItem(Item *item)
{
    m_holding_item = item;
}

Item *Entity::getHoldingItem()
{
    return m_holding_item;
}

Item *Entity::dropHoldingItem()
{
    Item *temp = m_holding_item;
    m_holding_item = nullptr;
    return temp;
}

Item *Entity::getRandomDropItem()
{
    return nullptr;
}

void Entity::setHitCircle(HitCircle hc)
{
    m_hc = hc;
}

void Entity::setOnClickFunction(OnClickFunction onclickfunct)
{
    m_onclickfunct = onclickfunct;
}

void Entity::onCliced()
{
    if (m_onclickfunct)
    {
        GET_FUN(m_onclickfunct)(this, m_quest_status == QuestStatus::QS_AVAILABLE);
        setQuestState(Object::QuestStatus::QS_NONE);
    }
}

EntityAI *Entity::getAI()
{
    return &m_ai;
}
#if 0
void Entity::DEBUGinitializeAI()
{
    if (!m_ai)
    {
        m_ai = new EntityAI();
        m_ai->setMovementSpeed(8.0F);
        m_ai->setDistanceVisibility(9.0F);
    }
}
#endif
void Entity::createProjectile(std::string owner)
{
    if (!m_projectile)
    {
        Vec2f dir = getProjectileDirection();
        m_projectile = new Projectile(m_pos + (dir * m_aabb.getSize())/* + (dir * (m_aabb.m_size / 2.0F)).negated().flipped()*/, float(gh::GH_DEFAULT_PROJECTILE_DIST_LIM));
        m_projectile->setDynamicVelocity(dir);
        m_projectile->m_drag = 0.0F;
        m_projectile->setTexture("projectile.png");
        m_projectile->setOwner(owner);
        // (dir * m_aabb.m_size) to put outside of source aabb
    }
}

Vec2f Entity::getProjectileDirection() const
{
    switch (m_orientation)
    {
    case OO_UP:
        return Vec2f(0.0F, -1.0F);
    case OO_DOWN:
        return Vec2f(0.0F, 1.0F);
    case OO_LEFT:
        return Vec2f(-1.0F, 0.0F);
    case OO_RIGHT:
        return Vec2f(1.0F, 0.0F);
    default:
        return Vec2f(0.0F, 0.0F);
    }
}

Projectile *Entity::getProjectile()
{
    Projectile *temp = m_projectile;
    m_projectile = nullptr;
    return temp;
}
