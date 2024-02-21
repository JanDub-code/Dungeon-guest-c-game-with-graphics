#include "base_scene.h"
#include <iostream>


BaseScene::BaseScene()
{
    m_loaded = false;
}

BaseScene::~BaseScene()
{
    clearContents();
}

void BaseScene::clearContents()
{
    for (auto o: m_objects)
    {
        if (o->getName() != "player"/*!dynamic_cast<Player*>(o)*/)
        {
            std::cout << "Object not player! Deleted. OK" << std::endl;
            delete o;
        }
        else
        {
            std::cout << "Player not deleted! OK" << std::endl;
        }
    }

    m_objects.clear();
    m_loaded = false;
}
#if 0
QVariant BaseScene::getObjects()
{
    return QVariant::fromValue(m_cache);
}
#endif
