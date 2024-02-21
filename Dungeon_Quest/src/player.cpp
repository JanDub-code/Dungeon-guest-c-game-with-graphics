#include "player.h"
//#include "game_header.h"
#include "vectors.h"
#include "keyboard.h"

Player::Player()
{
    m_name = "player";
    // TODO: Add difficulty for the game (a class or something?)
    setHealth(10);
    m_health = 9; // DEBUG
    m_strength = 1;
    m_protection = 0;
    //m_size = Vec2f(0.9F, 1.3F);
    m_drag = 0.0F;
    m_visual_size = Vec2i(16, 23);
    m_aabb = AABB(m_pos, Vec2f(0.9F, 1.3F));
    //m_visual_size = Vec2i(32);
    //m_aabb = AABB(m_pos, Vec2f(1.0F, 1.0F));
    m_ctrl_pressed = false;
    m_q_pressed = false;
}

Player::~Player()
{
}

void Player::update()
{
    //Entity::update();
    // TODO: Input controls. Movement and other behavior.
    //std::cout << "Key up pressed:" << gh_keys.isPressed(gh_keys.K_UP) << std::endl;
    //checkHotbarContent(); // TODO: Remove
    switchItemInput();
    m_holding_item = m_hotbar.getActiveItem(); // Temporary solution (to periodically update contents when hotbar is manipulated from the outside)
    // For emmiting projectiles
    DEBUGAttackInput();
}

void Player::fixedUpdate()
{
    float move_l = 0;
    float move_u = 0;

    movementImput(move_l, move_u);
    // add speed multiplier?
    // some other interactions before increment?
#ifndef CRAZY_PHYSICS
    m_velocity = Vec2f(move_l, move_u);
#else
    m_velocity += Vec2f(move_l, move_u);
#endif
    Physical::fixedUpdate();
    cameraMoveToObj(Camera::getInstance()); // Call function to fix camera pos
}

void Player::actionAttack(Entity *entity)
{
    // m_sound.setSource(QUrl("qrc:/src/assets/sounds/attack.mp3")); // INFO: default none
    Entity::actionAttack(entity);
}

void Player::actionGetAttacked(int ammount)
{
    m_sound.setSource(QUrl("qrc:/src/assets/sounds/hurt1.mp3")); // INFO: default none
    Entity::actionGetAttacked(ammount);
}

void Player::movementImput(float &l, float &u)
{
    // only "if" is being used to be able to move multiple directions (oposite directions equal to zero)
    if (Keyboard::isPressed(Keyboard::KKeys::K_UP) || Keyboard::isPressed(Keyboard::KKeys::K_W))
    {
        u -= gh::GH_PLAYER_SPEED;
        m_orientation = OO_UP;
        //forceModeVelocity(Vec2f(0.0F, -GH_PLAYER_SPEED * 2.0F));
    }
    if (Keyboard::isPressed(Keyboard::KKeys::K_DOWN) || Keyboard::isPressed(Keyboard::KKeys::K_S))
    {
        u += gh::GH_PLAYER_SPEED;
        m_orientation = OO_DOWN;
        //forceModeVelocity(Vec2f(0.0F, GH_PLAYER_SPEED * 2.0F));
    }
    if (Keyboard::isPressed(Keyboard::KKeys::K_LEFT) || Keyboard::isPressed(Keyboard::KKeys::K_A))
    {
        l -= gh::GH_PLAYER_SPEED;
        m_orientation = OO_LEFT;
        //forceModeVelocity(Vec2f(-GH_PLAYER_SPEED * 2.0F, 0.0F));
    }
    if (Keyboard::isPressed(Keyboard::KKeys::K_RIGHT) || Keyboard::isPressed(Keyboard::KKeys::K_D))
    {
        l += gh::GH_PLAYER_SPEED;
        m_orientation = OO_RIGHT;
        //forceModeVelocity(Vec2f(GH_PLAYER_SPEED * 2.0F, 0.0F));
    }
}

void Player::DEBUGAttackInput()
{
    if (Keyboard::isPressed(Keyboard::KKeys::K_LCONTROL) && !m_ctrl_pressed)
    {
        m_ctrl_pressed = true;
        createProjectile(m_name);
        //m_projectile->m_drag = 0.0F;
    }
    else if (!Keyboard::isPressed(Keyboard::KKeys::K_LCONTROL) && m_ctrl_pressed)
    {
        m_ctrl_pressed = false;
    }
}

void Player::switchItemInput()
{
    // flip-flop
    if (Keyboard::isPressed(Keyboard::KKeys::K_Q) && !m_q_pressed)
    {
        m_q_pressed = true;
        m_hotbar.switchItem();
        //m_holding_item = m_hotbar.getActiveItem();
    }
    else if (!Keyboard::isPressed(Keyboard::KKeys::K_Q) && m_q_pressed)
    {
        m_q_pressed = false;
    }
}

void Player::checkIfHotbarIsEmpty() // This is only a temporary check if items from hotbar are deleted but holding item is not nullptr. TODO: Remove
{
    a_items temp = m_hotbar.getAllItems();
    bool is_empty = true;

    for (auto i : temp)
    {
        if (i)
        {
            is_empty = false;
            break;
        }
    }

    if (is_empty)
    {
        m_holding_item = nullptr;
    }
}

void Player::checkHotbarContent() //TODO: Remove all
{
    if (!m_hotbar.getActiveItem())
    {
        m_holding_item = nullptr;
        return;
    }

    checkIfHotbarIsEmpty();
}

// TODO: create class hit radius for player and monster detection (if monster within player's radius and the way around)
//       also interactions in engine will be things like if player hits wall set velocity to 0 based on direction

// INFO: We can call Physical::update(); directly here but if we don't override fixedUpdate it is not needed.
