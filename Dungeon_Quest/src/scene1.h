#ifndef SCENE1_H
#define SCENE1_H

#include "base_scene.h"

class Scene1 : public BaseScene
{
public:
    Scene1() {}
    ~Scene1() {}
    void initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg) override;
    void loadAmbientMusic(QMediaPlayer &amb_mus) override;
};

#endif // SCENE1_H
