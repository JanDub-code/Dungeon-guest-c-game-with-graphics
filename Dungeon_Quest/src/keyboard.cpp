#include "keyboard.h"

Keyboard *Keyboard::m_instance = nullptr;
bool Keyboard::m_keys[m_key_count];
bool Keyboard::m_previous[m_key_count];

Keyboard::Keyboard()
{
    releaseAll();
}

Keyboard::~Keyboard()
{
}

void Keyboard::releaseAll()
{
    for (int i = 0; i < m_key_count; i++)
    {
        m_keys[i] = false;
        m_previous[i] = false;
    }
}

void Keyboard::setPressed(KKeys key)
{
    m_keys[static_cast<int>(key)] = true;
    m_previous[static_cast<int>(key)] = false;
}

void Keyboard::setReleased(KKeys key)
{
    m_keys[static_cast<int>(key)] = false;
    m_previous[static_cast<int>(key)] = true;
}

bool Keyboard::isPressed(KKeys key)
{
    return m_keys[static_cast<int>(key)];
}

bool Keyboard::isClicked(KKeys key)
{
    if(!m_keys[static_cast<int>(key)])
    {
        return false;
    }

    if(m_keys[static_cast<int>(key)] != m_previous[static_cast<int>(key)])
    {
        m_previous[static_cast<int>(key)] = m_keys[static_cast<int>(key)];
        return true;
    }

    return false;
}

void Keyboard::instantiate()
{
    if (!m_instance)
    {
        m_instance = new Keyboard();
    }
}

void Keyboard::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

Keyboard *Keyboard::getInstance()
{
    return m_instance;
}
