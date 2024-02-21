#ifndef SCENE5_H
#define SCENE5_H


#include "base_scene.h"

class Scene5 : public BaseScene
{
public:
    Scene5() {}
    ~Scene5() {}
    void initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg) override;
    void loadAmbientMusic(QMediaPlayer &amb_mus) override;
};
#endif // SCENE5_H
