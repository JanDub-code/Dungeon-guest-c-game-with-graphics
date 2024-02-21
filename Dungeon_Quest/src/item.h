#ifndef ITEM_H
#define ITEM_H

#include "physical.h"
#include <iostream>

// TODO: Pick up item from ground if in certain distance (if moved to inventory, remove pointer from vector of objects)

class Weapon;
// INFO: Probably parent/virtual class so classes like Sword, Potion etc. can be derived from it?
class Item : public Physical
{


private:
public:
    Item(QString photo);
    Item();
    ~Item();
    inline Item* asItem() override { return this; }
    virtual inline Weapon* asWeapon() { return nullptr; }
    inline const Weapon* asWeapon() const { return const_cast<Item*>(this)->asWeapon(); }
};

typedef std::vector<Item*> v_items;

#endif // ITEM_H
