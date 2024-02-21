#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Melee;
class Ranged;
// TODO: Add default weapon properties
class Weapon : public Item
{
    Q_OBJECT
protected:
    float m_harm; // TODO: no getters because ranged will produce projectile with set strength (projectile is entity)
public:
    Weapon(QString photo);
    Weapon();
    ~Weapon();
    inline Weapon* asWeapon() override { return this; }
    virtual inline Melee* asMelee() { return nullptr; }
    inline const Melee* asMelee() const { return const_cast<Weapon*>(this)->asMelee(); }
    virtual inline Ranged* asRanged() { return nullptr; }
    inline const Ranged* asRanged() const { return const_cast<Weapon*>(this)->asRanged(); }

    void setHarmAmmount(float harm);
};

#endif // WEAPON_H
