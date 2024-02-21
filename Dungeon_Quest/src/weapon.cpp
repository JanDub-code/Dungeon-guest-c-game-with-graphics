#include "weapon.h"

Weapon::Weapon()
{
    m_name = "weapon";
    m_harm = 1.0F;
}

Weapon::Weapon(QString photo) : Item(photo)
{
    m_name = "weapon";
    m_harm = 1.0F;
}

Weapon::~Weapon()
{

}

void Weapon::setHarmAmmount(float harm)
{
    m_harm = harm;
}
