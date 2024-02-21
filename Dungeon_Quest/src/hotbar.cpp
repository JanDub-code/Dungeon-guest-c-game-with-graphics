#include "hotbar.h"

Hotbar::Hotbar()
{
    initItems();
    m_held_item_index = 0;
}

Hotbar::~Hotbar()
{

}

bool Hotbar::addItem(Item *item)
{
    for (int i = 0; i < gh::GH_HOTBAR_SIZE; i++)
    {
        if (!m_items[i])
        {
            m_items[i] = item;
            emit itemsModified();
            return true;
        }
    }

    return false;
}

Item *Hotbar::withdrawSelectedItem()
{
    Item *temp = m_items[m_held_item_index];
    m_items[m_held_item_index] = nullptr;
    emit itemsModified();
    return temp;
}

QVariant Hotbar::getItems() const
{
    return QVariant::fromValue<a_items>(m_items);
}

void Hotbar::switchItem()
{
    if (m_held_item_index < gh::GH_HOTBAR_SIZE - 1)
    {
        m_held_item_index++;
        emit itemSwitched();
        return;
    }

    m_held_item_index = 0;
    emit itemSwitched();
}

int Hotbar::getHotbarIndex() const
{
    return m_held_item_index;
}

a_items Hotbar::getAllItems()
{
    return m_items;
}

void Hotbar::initItems()
{
    for (size_t i = 0; i < gh::GH_HOTBAR_SIZE; i++)
    {
        m_items[i] = nullptr;
    }
}
