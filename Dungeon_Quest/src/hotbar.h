#ifndef HOTBAR_H
#define HOTBAR_H

#include "item.h"
#include <array>
#include "game_header.h"
#include <QObject>

// INFO: Always has the same size (even if multiple classes are using it as own object)
typedef std::array<Item*, gh::GH_HOTBAR_SIZE> a_items;

class Hotbar : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant items READ getItems NOTIFY itemsModified)
    Q_PROPERTY(int item_index READ getHotbarIndex NOTIFY itemSwitched)
private:
    a_items m_items;
    int m_held_item_index; // INFO: This index makes more sense here than in inventory when we are using QML
public:
    Hotbar();
    ~Hotbar();
    bool addItem(Item *item);
    Item *withdrawSelectedItem();
    inline Item *getActiveItem()
    { return m_items[m_held_item_index]; }
    QVariant getItems() const;
    void switchItem();
    int getHotbarIndex() const; // for QML
    a_items getAllItems();
private:
    void initItems();
signals:
    void itemsModified();
    void itemSwitched(); // To be able to show rectangle which item is selected
};

#endif // HOTBAR_H
