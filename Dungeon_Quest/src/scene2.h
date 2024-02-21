#ifndef SCENE2_H
#define SCENE2_H

#include "base_scene.h"

class Scene2 : public BaseScene
{
public:
    Scene2() {}
    ~Scene2() {}
    void initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg) override;
    void loadAmbientMusic(QMediaPlayer &amb_mus) override;
};

#endif // SCENE2_H
