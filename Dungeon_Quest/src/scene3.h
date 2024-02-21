#ifndef SCENE3_H
#define SCENE3_H


#include "base_scene.h"

class Scene3 : public BaseScene
{
public:
    Scene3() {}
    ~Scene3() {}
    void initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg) override;
    void loadAmbientMusic(QMediaPlayer &amb_mus) override;
};

#endif // SCENE3_H
