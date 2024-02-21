#include "ranged.h"

Ranged::Ranged()
{
    m_name = "ranged";
}

Ranged::Ranged(QString photo) : Weapon(photo)
{
    m_name = "ranged";
}


Ranged::~Ranged()
{

}
