#ifndef __PLAYER__
#define __PLAYER__

#include "entity.h"
#include "item.h"
#include <array>
#include "game_header.h"
#include "hotbar.h"

//#define CRAZY_PHYSICS

typedef std::array<Item*, gh::GH_HOTBAR_SIZE> a_items;

class Player : public Entity
{
    Q_OBJECT
private:
    bool m_ctrl_pressed;
    bool m_q_pressed;
public:
    Hotbar m_hotbar;

    Player();
    ~Player();
    inline Player* asPlayer() override { return this; }
    void update() override;
    void fixedUpdate() override;
    void actionAttack(Entity *entity) override; // TODO: Rename to something more clear (attack or something)
    void actionGetAttacked(int ammount) override;
private:
    void movementImput(float &l, float &u);
    void DEBUGAttackInput();
    void switchItemInput();
    void checkIfHotbarIsEmpty();
    void checkHotbarContent();
};

#endif
