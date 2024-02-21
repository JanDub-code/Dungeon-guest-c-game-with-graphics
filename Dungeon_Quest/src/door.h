#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include "physical.h"

class Door : public Physical
{
    Q_OBJECT
private:
    bool m_is_locked;
    size_t m_level_id;
    Vec2f m_target_location;
    //Vec2f m_one_way_destination;
    //Door *m_destination;
public:
    Door(size_t target_level_id, Vec2f target_location);
    ~Door();
    inline Door* asDoor() override { return this; }
    void setOneWayDestination(Vec2f dest);
    //void setDestination(Door *dest);
    bool isLocked();
    void lock();
    void unlock();
    inline size_t getLevelID()
    { return m_level_id; }
    inline Vec2f getTargetLocation()
    { return m_target_location; }
};

#endif // DOOR_H

// TODO: Make transition between levels possible.
//       Remove player initialization for each level. Do it for first level only and then player will be inserted to the front of the m_objects vector of the specific level.
//       Level = vector of objects + vector of tiles. m_level_id is the id of specific m_objects + m_tiles.
//       Make std::vector<std:vectorObject*>> m_levels or std:vectorObject*> m_level, std:vectorObject*> m_level1
