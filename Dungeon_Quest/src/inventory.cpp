#include "inventory.h"
#include "dqmath.h"

v_items Inventory::m_items;
int Inventory::m_selector = 0;
// To make it simpler
int Inventory::m_width = 1;
int Inventory::m_height = 1;
Inventory *Inventory::m_instance = nullptr;

Inventory::Inventory(int w, int h)
{
    m_selector = 0;
    m_width = w;
    m_height = h;
    setup(m_width, m_height);
}

Inventory::~Inventory()
{
    for (auto i : m_items)
    {
        delete i;
    }
}

void Inventory::setup(int w, int h)
{
    v_items temp(w * h, nullptr);

    for (auto i : m_items)
    {
        delete i;
    }

    m_items.clear();
    m_items = temp;
    if (m_instance)
    { emit m_instance->itemsModified(); }
}

Item *Inventory::getSelectedItem()
{
    return m_items[m_selector];
}

void Inventory::setSelectedItem(Item *item)
{
    m_items[m_selector] = item;
}

bool Inventory::addItem(Item *item)
{
    for (int i = 0; i < int(m_items.size()); i++)
    {
        if (!m_items[i])
        {
            m_items[i] = item;
            emit m_instance->itemsModified();
            return true;
        }
    }

    return false;
}

QVariant Inventory::getInventoryItems()
{
    return QVariant::fromValue(m_items);
}
// INFO: reset() and nullptr is pretty much the same thing
void Inventory::removeSelectedItem()
{
    delete m_items[m_selector];
    m_items[m_selector] = nullptr;
}

void Inventory::removeItem(int index)
{
    // INFO: Fast functions (frequently used, short and inline)
    //       should not have these checks (it should be checked from the outside first)
    // DRY... but there is no time for perfectionism
    if (index >= m_width * m_height)
    {
        return;
    }

    delete m_items[index];
    m_items[index] = nullptr;
}

void Inventory::removeItem(int x, int y)
{
    // TODO: Add size check (if needed)
    int index = DQMath::xyToVec1(x, y, m_width);
    delete m_items[index];
    m_items[index] = nullptr;
}

void Inventory::selectItem(int index)
{
    // INFO: Fast functions (frequently used, short and inline)
    //       should not have these checks (it should be checked from the outside first)
    // DRY... but there is no time for perfectionism
    if (index >= m_width * m_height)
    {
        return;
    }

    m_selector = index;
}

void Inventory::selectItem(int x, int y)
{
    // TODO: Add size check (if needed)
    m_selector = DQMath::xyToVec1(x, y, m_width);
}

int Inventory::getWidth()
{
    return m_width;
}

int Inventory::getHeight()
{
    return m_height;
}

void Inventory::instantiate(int w, int h)
{
    if (!m_instance)
    {
        m_instance = new Inventory(w, h);
    }
}

void Inventory::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

Inventory *Inventory::getInstance()
{
    return m_instance;
}

v_items Inventory::getInv()
{
    return m_items;
}

