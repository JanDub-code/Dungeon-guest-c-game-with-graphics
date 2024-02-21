#ifndef ENTITY_H
#define ENTITY_H

#include "physical.h"
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>
#include "item.h"
#include "hit_circle.h"
#include "entity_ai.h"

class Projectile;
class Interactive;
class Quest;
class Monster;

#define GET_FUN(x) x
//std::function<Quest*(void)> &funct
typedef void(*OnClickFunction) (Object*, bool);

class Entity : public Physical
{
    Q_OBJECT
    // TODO: If we really want to see health of entities we should add isEntity() throughout objects to access this function (because it is derived)
    Q_PROPERTY(int health READ getHealth NOTIFY healthChanged)
    Q_PROPERTY(int health_max READ getHealthMax NOTIFY healthMaxChanged)
protected:
    int m_health;
    int m_health_max;
    int m_strength;
    int m_protection;
    Item *m_holding_item;
    Projectile *m_projectile;
    EntityAI m_ai;
    //Armor *m_armor;
private:
    QAudioOutput m_aud_out;
protected:
    HitCircle m_hc;
    QMediaPlayer m_sound;
    OnClickFunction m_onclickfunct;
public:
    Entity();
    ~Entity();
    inline Entity* asEntity() override { return this; }
    virtual void update() override;
    void setHealth(int health);
    int getHealth();
    int getHealthMax();
    void addHealth(int ammount);
    virtual void actionAttack(Entity *entity); // TODO: Rename to something more clear (attack or something)
    virtual inline Projectile* asProjectile() { return nullptr; }
    inline const Projectile* asProjectile() const { return const_cast<Entity*>(this)->asProjectile(); }
    virtual inline Interactive* asInteractive() { return nullptr; }
    inline const Interactive* asInteractive() const { return const_cast<Entity*>(this)->asInteractive(); }
    virtual inline Monster* asMonster() { return nullptr; }
    inline const Monster* asMonster() const { return const_cast<Entity*>(this)->asMonster(); }
    virtual void actionGetAttacked(int ammount);
    void setHoldingItem(Item *item);
    Item *getHoldingItem();
    Item *dropHoldingItem();
    virtual Item *getRandomDropItem();
    void setHitCircle(HitCircle hc);
    inline HitCircle getHitCircle()
    { return m_hc; }

    void setOnClickFunction(OnClickFunction onclickfunct);
    void onCliced();

    EntityAI *getAI();

    //virtual void fixedUpdateAI(Object *obj) {}
    //void DEBUGinitializeAI();
protected:
    void createProjectile(std::string owner);
    Vec2f getProjectileDirection() const;
public:
    // Returns projectile and forgets it
    Projectile* getProjectile();
    //void setArmor(Armor *armor);
    //Armor *getArmor();
signals:
    void healthChanged();
    void healthMaxChanged();
};

#endif // ENTITY_H

// TODO: If we want to be able to swing with weapon with no other entity being around
//       then maybe add function called swingWeapon() and call it before calling actionAttack
//       to make a weapon swing sound without attacking anything
