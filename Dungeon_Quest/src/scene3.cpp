#include "scene3.h"
#include "monster.h"
#include "event_logger.h"
#include "door.h"

void Scene3::initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg)
{
    tg.setMap(3);
    tiles = tg.getCppTiles();

    //player->setPos(Vec2f(1.0F, 1.0F));
    //m_objects.push_back(player);
    Door *door(new Door(0, Vec2f(6.01F,15.01F)));
    door->setPos(Vec2f(5.0F,1.0F));
    door->setTexture("Portals/portal_red.png");
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
    mon->setTexture("soldier.png");
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
    mon1->setTexture("necromancer.png");
    m_objects.push_back(mon1);

    Monster *mon2(new Monster());
    mon2->setPos(Vec2f(4.0F, 12.0F));
    mon2->setHealth(11);
    mon2->setNonSolid();
    mon2->getAI()->setEnabled();
    mon2->getAI()->setAttackEnabled();
    mon2->getAI()->setAttackCooldown(0.5F);
    mon2->getAI()->setMovementSpeed(8.0F);
    mon2->getAI()->setDistanceVisibility(9.0F);
    mon2->setTexture("axeman.png");
    m_objects.push_back(mon2);

    logEvent("SceneLoader1", EventLogger::LogType::LOG_TYPE_INFO, "Scene loaded successfuly!");
    m_loaded = true;
}

void Scene3::loadAmbientMusic(QMediaPlayer &amb_mus)
{
    amb_mus.setSource(QUrl("qrc:/src/assets/sounds/The_Arrival_(BATTLE_II).mp3")); // something else
    }
