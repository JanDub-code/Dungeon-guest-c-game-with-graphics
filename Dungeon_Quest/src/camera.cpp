#include "camera.h"
#include "game_header.h"

int Camera::m_width = 0;
int Camera::m_heihgt = 0;
int Camera::m_borders_x = 0;
int Camera::m_borders_y = 0;
bool Camera::m_pos_changed = false;
Camera *Camera::m_instance = nullptr;
Vec2f Camera::m_pos = Vec2f(0.0F);

Camera::Camera()
{
    m_width = gh::GH_SCREEN_W;
    m_heihgt = gh::GH_SCREEN_H;
    m_pos = Vec2f(0.0F, 0.0F);
    m_borders_x = 1.0F;
    m_borders_y = 1.0F;
    m_pos_changed = false;
}

Camera::~Camera()
{
}

Vec2i Camera::getDimensions()
{
    return Vec2i(m_width, m_heihgt);
}

int Camera::getWidth()
{
    return m_width;
}

int Camera::getHeight()
{
    return m_heihgt;
}

void Camera::setBorderX(float x)
{

    m_borders_x = x;
}

void Camera::setBorderY(float y)
{
    m_borders_y = y;
}

int Camera::getBorderX()
{
    return m_borders_x;
}

int Camera::getBorderY()
{
    return m_borders_y;
}

float Camera::getPosX()
{
    return m_pos.x;
}

float Camera::getPosY()
{
    return m_pos.y;
}

void Camera::setPosChanged()
{
    m_pos_changed = true;
}

void Camera::resetPosChanged()
{
    m_pos_changed = false;
}

bool Camera::posChanged()
{
    return m_pos_changed;
}

void Camera::instantiate()
{
    if (!m_instance)
    {
        m_instance = new Camera();
    }
}

void Camera::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

Camera *Camera::getInstance()
{
    return m_instance;
}
