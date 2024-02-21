#ifndef SCENE0_H
#define SCENE0_H

#include "base_scene.h"

class Scene0 : public BaseScene
{
public:
    Scene0() {}
    ~Scene0() {}
    void initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg) override;
    void loadAmbientMusic(QMediaPlayer &amb_mus) override;
};

#endif // SCENE0_H
