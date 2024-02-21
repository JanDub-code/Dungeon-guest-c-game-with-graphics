#include "ray.h"

Ray::Ray()
{

}

Ray::Ray(Vec2f origin, Vec2f end)
{
    m_origin = origin;
    m_end = end;
}
