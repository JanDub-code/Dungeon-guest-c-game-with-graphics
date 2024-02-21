#ifndef __CUTSCENE__
#define __CUTSCENE__

#include <QObject>
#include <QVariant>
//#include "Vectors.h" // TODO: To .cpp and for derived classes only
#include "camera.h"
#include "player.h"
#include "object.h"

// Does not have to be QObject because it only interacts with the objects. It is not part of Qt objects
// Usage example: Set number of frames, Frame1: set cam pos, set objects pos
// TODO: Ignore if too hard and time consuming
class Cutscene
{
private:
    int m_frame_count = 0;
    int m_current_frame = 0;
    std::vector<int> m_object_ids; // for each pos vector line to point to right object in all objects
    std::vector<std::vector<Vec2i>> m_frames; // each line contains vector of animation positions for individual object
public:
    // TODO: use emit when cutscene is running
    Cutscene();
    ~Cutscene();
    void setFrameCount(int frames);
    virtual void loadCutscene(v_objects &objects, Player &player, Camera &cam) {/*things like m_frames.append() for animations*/}

    // Similar to update but animations are deltaTime dependent
    virtual void runFrame(v_objects &objects, Player &player, Camera &cam);

    bool isFinished();
};

#endif

// INFO: The main difference between Cutscene and Scene is that Scene loads all objects for gameplay
//       but Cutscene can manipulate with the existing objects
