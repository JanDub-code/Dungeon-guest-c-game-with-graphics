#include "cutscene.h"
//#include "game_header.h"


Cutscene::Cutscene()
{
}

Cutscene::~Cutscene()
{
}

void Cutscene::setFrameCount(int frames)
{
    m_frame_count = frames;
}

void Cutscene::runFrame(v_objects &objects, Player &player, Camera &cam)
{
    // virtual: do some stuff before increment
    // if smooth animatuion, increment only after first smooth animation is finished
    m_current_frame++;
}

bool Cutscene::isFinished()
{
    return (m_current_frame >= m_frame_count /*or use m_frames.size()*/);
}
