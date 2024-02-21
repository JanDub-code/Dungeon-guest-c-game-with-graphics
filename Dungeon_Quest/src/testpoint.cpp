#include "testpoint.h"

TestPoint::TestPoint()
{

}

int TestPoint::getPosCamRelX()
{
    return int(m_pos.x);
}

int TestPoint::getPosCamRelY()
{
    return int(m_pos.y);
}
