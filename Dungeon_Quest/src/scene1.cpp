#include "scene1.h"
#include "event_logger.h"
#include "monster.h"
#include "door.h"
#include "melee.h"

void Scene1::initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg)
{
    tg.setMap(1);
    tiles = tg.getCppTiles();

    Door *door(new Door(0, Vec2f(7.01F,15.01F)));
    door->setPos(Vec2f(1.0F,5.0F));
    door->setTexture("Portals/portal_green.png");
    m_objects.push_back(door);

    Door *door1(new Door(5, Vec2f(2.01F,2.01F)));
    door1->setPos(Vec2f(16.0F,1.0F));
    door1->setTexture("Portals/portal_purple.png");
    m_objects.push_back(door1);
    Monster *mon(new Monster());

    mon->setPos(Vec2f(4.0F, 3.0F));
    mon->setHealth(11);
    mon->setNonSolid();
    mon->getAI()->setEnabled();
    mon->getAI()->setAttackEnabled();
    mon->getAI()->setAttackCooldown(0.5F);
    mon->getAI()->setMovementSpeed(8.0F);
    mon->getAI()->setDistanceVisibility(9.0F);
    mon->setTexture("soldier.png");
    Melee *sword = new Melee();
    sword->setTexture("weapon1_gnd.png");
    sword->setPhoto("weapon1.png");
    mon->setHoldingItem(sword);
    m_objects.push_back(mon);

    Monster *mon1(new Monster());
    mon1->setPos(Vec2f(7.0F, 5.0F));
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
    mon2->setPos(Vec2f(13.0F, 4.0F));
    mon2->setHealth(11);
    mon2->setNonSolid();
    mon2->getAI()->setEnabled();
    mon2->getAI()->setAttackEnabled();
    mon2->getAI()->setAttackCooldown(0.5F);
    mon2->getAI()->setMovementSpeed(8.0F);
    mon2->getAI()->setDistanceVisibility(9.0F);
    mon2->setTexture("axeman.png");
    m_objects.push_back(mon2);

    Monster *mon3(new Monster());
    mon3->setPos(Vec2f(16.0F, 3.0F));
    mon3->setHealth(11);
    mon3->setNonSolid();
    mon3->getAI()->setEnabled();
    mon3->getAI()->setAttackEnabled();
    mon3->getAI()->setAttackCooldown(0.5F);
    mon3->getAI()->setMovementSpeed(8.0F);
    mon3->getAI()->setDistanceVisibility(9.0F);
    mon3->setTexture("golem.png");
    m_objects.push_back(mon3);

    logEvent("SceneLoader1", EventLogger::LogType::LOG_TYPE_INFO, "Scene loaded successfuly!");
    m_loaded = true;
}

void Scene1::loadAmbientMusic(QMediaPlayer &amb_mus)
{
    amb_mus.setSource(QUrl("qrc:/src/assets/sounds/The_Arrival_(BATTLE_II).mp3")); // something else
}
