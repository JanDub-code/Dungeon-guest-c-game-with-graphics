#include "mouse.h"
#include "camera.h"
#include "game_header.h"

Mouse *Mouse::m_instance = nullptr;
bool Mouse::m_buttons[m_button_count];
bool Mouse::m_previous[m_button_count];
Vec2f Mouse::m_pos = Vec2f(0.0F);
Mouse::MCursors Mouse::m_cursor = Mouse::MCursors::C_DEFAULT;

Mouse::Mouse()
{
    releaseAll();
}

Mouse::~Mouse()
{

}

void Mouse::releaseAll()
{
    for (int i = 0; i < m_button_count; i++)
    {
        m_buttons[i] = false;
        m_previous[i] = false;
    }
}

void Mouse::setPressed(MButtons button)
{
    m_buttons[static_cast<int>(button)] = true;
    m_previous[static_cast<int>(button)] = false;
}

void Mouse::setReleased(MButtons button)
{
    m_buttons[static_cast<int>(button)] = false;
    m_previous[static_cast<int>(button)] = true;
}

bool Mouse::isPressed(MButtons button)
{
    return m_buttons[static_cast<int>(button)];
}

bool Mouse::isClicked(MButtons button)
{
    if(!m_buttons[static_cast<int>(button)])
    {
        return false;
    }

    if(m_buttons[static_cast<int>(button)] != m_previous[static_cast<int>(button)])
    {
        m_previous[static_cast<int>(button)] = m_buttons[static_cast<int>(button)];
        return true;
    }

    return false;
}

void Mouse::setX(int x)
{
    m_pos.x = float(x);
}

void Mouse::setY(int y)
{
    m_pos.y = float(y);
}

Mouse::MCursors Mouse::getCursor()
{
    return m_cursor;
}

void Mouse::setCursor(MCursors cur)
{
    m_cursor = cur;
    emit m_instance->mouseCursorChanged();
}

Vec2f Mouse::getPos()
{
    return m_pos;
}

// For quicker access to mouse coordinates translated to tile coords
Vec2f Mouse::getTileTransformedPos()
{
    Vec2f cam_shifted = Vec2f(Camera::getPos().x * gh::GH_DEFAULT_TILE_VISUAL_SIZE_F - gh::GH_SCREEN_W_HALF_F,
                              Camera::getPos().y * gh::GH_DEFAULT_TILE_VISUAL_SIZE_F - gh::GH_SCREEN_H_HALF_F);
    return Vec2f(cam_shifted + m_pos) / gh::GH_DEFAULT_TILE_VISUAL_SIZE_F;
}

void Mouse::instantiate()
{
    if (!m_instance)
    {
        m_instance = new Mouse();
    }
}

void Mouse::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

Mouse *Mouse::getInstance()
{
    return m_instance;
}
