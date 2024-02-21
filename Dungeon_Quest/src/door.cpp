#include "door.h"

Door::Door(size_t target_level_id, Vec2f target_location)
{
    m_name = "door";
    m_is_locked = false;
    m_is_solid = false;
    m_level_id = target_level_id;
    m_target_location = target_location;
    //m_visible = false;
}

Door::~Door()
{

}

bool Door::isLocked()
{
    return m_is_locked;
}
