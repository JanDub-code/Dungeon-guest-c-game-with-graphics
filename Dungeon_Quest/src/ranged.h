#ifndef RANGED_H
#define RANGED_H

#include "weapon.h"
// TODO: Add properties to create new Projectile with set strength aka damage
//       strength because Projectile is now Entity... maybe add BasicEntity with almost no porperties and then Entity as derived?
class Ranged : public Weapon
{
public:
    Ranged();
    Ranged(QString photo);
    ~Ranged();
    virtual inline Ranged* asRanged() { return this; }
};

#endif // RANGED_H
