#include "monster.h"

Monster::Monster()
{
    m_name = "monster";
    //m_drag = 0.0F;
}

Monster::~Monster()
{
}
#if 0
void Monster::fixedUpdateAI(Object *obj)
{
    if (!m_ai)
    { return; }
    m_ai->followObject(this, obj);
}
#endif
