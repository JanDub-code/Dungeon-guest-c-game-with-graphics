#ifndef MONSTER_H
#define MONSTER_H

#include "entity.h"

class Monster : public Entity
{
    Q_OBJECT
private:
public:
    Monster();
    ~Monster();
    inline Monster* asMonster() override { return this; }
    //virtual void fixedUpdateAI(Object *obj) override;
};

#endif // MONSTER_H
