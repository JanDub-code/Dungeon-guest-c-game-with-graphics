#ifndef MELEE_H
#define MELEE_H

#include "weapon.h"
// TODO: Add properties like sharpness etc.
class Melee : public Weapon
{
public:
    Melee();
    ~Melee();
    virtual inline Melee* asMelee() { return this; }

    inline float getHarmAmmount()
    { return m_harm; }
};

#endif // MELEE_H
