#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include "item.h"
#include "game_header.h"

class Inventory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant invItems READ getInventoryItems NOTIFY itemsModified)
private:
    static v_items m_items;
    static int m_selector;
    // To make it simpler
    static int m_width;
    static int m_height;
    static Inventory *m_instance;

    Inventory(int w = gh::GH_INVENTORY_WIDTH, int h = gh::GH_INVENTORY_HEIGHT);
    ~Inventory();
public:
    // Base constructor if needed to call setup just from QML? TODO: Remove if useless
    static v_items getInv();
    // prepares key values
    Q_INVOKABLE static void setup(int w, int h); // TODO: Remove Q_INVOKABLE if useless

    static Item *getSelectedItem();
    // Use when populating item or when dropping item (nullptr). This function is universal
    static void setSelectedItem(Item *item);
    static bool addItem(Item *item);
    static QVariant getInventoryItems();
    Q_INVOKABLE static void removeSelectedItem();
    static void removeItem(int index);
    Q_INVOKABLE static void removeItem(int x, int y);

    static void selectItem(int index);
    Q_INVOKABLE static void selectItem(int x, int y);
    Q_INVOKABLE static int getWidth();
    Q_INVOKABLE static int getHeight();
    static void instantiate(int w, int h);
    static void destroy();
    static Inventory *getInstance();
signals:
    void itemsModified();
};

#endif // INVENTORY_H

// IMPORTANT: push_back should not be used to prevent size checks
//            and to make it faster when accessing items (inventory size is constant)

// HINT: If item is dropped set item pos to players position (and maybe set timer to be picked up again when standing close? But not here!!)
