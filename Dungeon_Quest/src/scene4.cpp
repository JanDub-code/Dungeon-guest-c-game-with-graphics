#include "scene4.h"
#include "event_logger.h"
#include "door.h"
#include "monster.h"

void Scene4::initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg)
{
    tg.setMap(4);
    tiles = tg.getCppTiles();

    //player->setPos(Vec2f(1.0F, 1.0F));
    //m_objects.push_back(player);
    Door *door(new Door(0, Vec2f(10.01F,3.01F)));
    door->setPos(Vec2f(5.0F,1.0F));
    door->setTexture("Portals/portal_blue.png");
    m_objects.push_back(door);

    Monster *mon(new Monster());
    mon->setPos(Vec2f(8.0F, 10.0F));
    mon->setHealth(11);
    mon->setNonSolid();
    mon->getAI()->setEnabled();
    mon->getAI()->setAttackEnabled();
    mon->getAI()->setAttackCooldown(0.5F);
    mon->getAI()->setMovementSpeed(8.0F);
    mon->getAI()->setDistanceVisibility(9.0F);
    mon->setTexture("boss_bee.png");
    m_objects.push_back(mon);

    Monster *mon1(new Monster());
    mon1->setPos(Vec2f(5.0F, 7.0F));
    mon1->setHealth(11);
    mon1->setNonSolid();
    mon1->getAI()->setEnabled();
    mon1->getAI()->setAttackEnabled();
    mon1->getAI()->setAttackCooldown(0.5F);
    mon1->getAI()->setMovementSpeed(8.0F);
    mon1->getAI()->setDistanceVisibility(9.0F);
    mon1->setTexture("boss_bee.png");
    m_objects.push_back(mon1);

    Item *prachy(new Item());
    prachy->asItem();
    prachy->setPos(Vec2f(6.0F,5.0F));
    prachy->setName("Prachy");
    prachy->setNonSolid();
    prachy->setTexture("bag1.png");
    prachy->setPhoto("../bag1.png");
    m_objects.push_back(prachy);

    Item *prachy1(new Item());
    prachy1->asItem();
    prachy1->setPos(Vec2f(4.0F,3.0F));
    prachy1->setName("Prachy");
    prachy1->setNonSolid();
    prachy1->setTexture("bag1.png");
    prachy1->setPhoto("../bag1.png");
    m_objects.push_back(prachy1);

    Item *prachy2(new Item());
    prachy2->asItem();
    prachy2->setPos(Vec2f(7.0F,8.0F));
    prachy2->setName("Prachy");
    prachy2->setNonSolid();
    prachy2->setTexture("bag1.png");
    prachy2->setPhoto("../bag1.png");
    m_objects.push_back(prachy2);

    logEvent("SceneLoader1", EventLogger::LogType::LOG_TYPE_INFO, "Scene loaded successfuly!");
    m_loaded = true;
}

void Scene4::loadAmbientMusic(QMediaPlayer &amb_mus)
{
    amb_mus.setSource(QUrl("qrc:/src/assets/sounds/Celestial.mp3")); // something else
    }
