#include "scene2.h"
#include "event_logger.h"
#include "door.h"
#include "monster.h"
#include "item.h"

void Scene2::initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg)
{
    tg.setMap(2);
    tiles = tg.getCppTiles();

    //player->setPos(Vec2f(1.0F, 1.0F));
    //m_objects.push_back(player);
    Door *door(new Door(0, Vec2f(2.01F,3.01F)));
    door->setPos(Vec2f(5.0F,1.0F));
    door->setTexture("Portals/portal_azure.png");
    m_objects.push_back(door);

    Monster *mon(new Monster());
    mon->setPos(Vec2f(3.0F, 14.0F));
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
    mon1->setPos(Vec2f(5.0F, 8.0F));
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
    prachy->setPos(Vec2f(4.0F,12.0F));
    prachy->setName("QPrachy");
    prachy->setNonSolid();
    prachy->setTexture("bag1.png");
    prachy->setPhoto("../bag1.png");
    m_objects.push_back(prachy);

    logEvent("SceneLoader1", EventLogger::LogType::LOG_TYPE_INFO, "Scene loaded successfuly!");
    m_loaded = true;
}

void Scene2::loadAmbientMusic(QMediaPlayer &amb_mus)
{
    amb_mus.setSource(QUrl("qrc:/src/assets/sounds/Celestial.mp3")); // something else
    }
