#ifndef SCENE4_H
#define SCENE4_H


#include "base_scene.h"

class Scene4 : public BaseScene
{
public:
    Scene4() {}
    ~Scene4() {}
    void initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg) override;
    void loadAmbientMusic(QMediaPlayer &amb_mus) override;
};

#endif // SCENE4_H
