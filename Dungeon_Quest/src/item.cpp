#include "item.h"

Item::Item()
{
    m_photo = "";
    m_is_solid = false;
}

Item::Item(QString photo)
{
    m_photo = photo;
    m_is_solid = false;
}

Item::~Item()
{

}
