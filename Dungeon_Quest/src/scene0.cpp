#include "scene0.h"
#include "event_logger.h"
#include "interactive.h"
#include <iostream>
#include "game_state.h"
#include "mouse.h"
#include "quest.h"
#include "game_engine.h"
#include "textbox.h"
#include "monster.h"
#include "door.h"
#include <iostream>

// INFO: quest_available means if not created then it can be created
#define OBJONCLICKFUN [](Object* obj, bool quest_available)->void

void Scene0::initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg)
{
    // Tiles
    tg.setMap(0);
    std::cout << "\nDEBUG\n" << std::endl;
    tiles = tg.getCppTiles();
    std::cout << "\nDEBUG\n" << std::endl;

    // Scripts
    auto onclick = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 20 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 20 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick1 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::cout << "Clicked on " + obj->getName() + " and created quest!" << quest_available << std::endl;
            std::string quest_object = "Dave";
            std::string quest_title = "Talk to my friend " + quest_object + "!";
            std::string quest_context = "Talk to " + quest_object + " and tell him\n I sended you\n\nRewards: 5 coins";
            std::string quest_end_context = "Thank you.\nFinally we can be ready!\nHere are 5 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            Interactive *ent = new Interactive();
            ent->setPos(Vec2f(7.0F, 8.0F));
            ent->setVelocity(Vec2f(5.0F, 0.0F));
            ent->setName("Dave"); // INFO: not necessary. This is for unasigned objects when only name is added for all objects with the same name
            ent->setTexture("hat-guy.png");
#if 1
            auto onclick1_inside = OBJONCLICKFUN
            {
                //GameEngine:: // TODO: something with claiming quest when clicking on target aka Dave.
                GameState::setState(GameState::State::GS_TEXTBOX_POPUP);
                Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
                TextBox::setMessages({ {"Hello I'm Dave."}, {"I have a quest for you!"}, {"Evil bees stole my bag with diamonds. Please bring it back to me."}, {"I will reward you greatly for your struggle!"} });
                std::cout << obj->getName() + " clicked using onclick function from lambda!\nHas quest: " << quest_available << std::endl;
            };
            ent->setOnClickFunction(onclick1_inside);
#endif
            quest->setTargetObject(ent);
            GameEngine::addObject(ent);
            quest->setTargetName(quest_object);
            quest->setQuestType(Quest::QType::QT_TALK);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick2 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon2!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 10 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 10 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick3 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon3!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 50 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 50 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick4 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon4!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 20 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 20 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick5 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon5!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 20 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 20 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick6 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon6!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 20 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 20 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick7 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon7!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 20 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 20 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick8 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon8!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 20 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 20 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };
    auto onclick9 = OBJONCLICKFUN
    {
        if (quest_available)
        {
            std::string quest_object = "diamond";
            std::string quest_title = "Crafting a new weapon9!";
            std::string quest_context = "Bring me a " + quest_object + " so I can\nmake a new weapon!\n\nRewards: 20 coins";
            std::string quest_end_context = "Thank you. Finally I can make the sword!\nHere are 20 coins.";
            Quest *quest = new Quest(obj, quest_title, quest_context, quest_end_context);
            quest->setTargetName(quest_object);
            obj->setQuestState(Object::QuestStatus::QS_NONE);
            GameEngine::newQuest(quest); // adds new quest to game engine
            logEvent("Interactive entity", EventLogger::LogType::LOG_TYPE_INFO, "Clicked!");
            // TODO: If no quest then no popup.
            GameState::setState(GameState::State::GS_QUEST_POPUP);
            Mouse::setCursor(Mouse::MCursors::C_DEFAULT);
        }
    };

    // Objects
    //player->setPos(Vec2f(3.0F, 5.0F));
    //m_objects.push_back(player);
    //
    Door *door2(new Door(2, Vec2f(2.01F)));
    door2->setPos(Vec2f(1.0F,1.0F));
    door2->setTexture("Portals/portal_azure.png");
    m_objects.push_back(door2);
    //
    Door *door3(new Door(3, Vec2f(2.01F)));
    door3->setPos(Vec2f(4.0F,17.0F));
    door3->setTexture("Portals/portal_red.png");
    m_objects.push_back(door3);
    //
    Door *door4(new Door(4, Vec2f(2.01F)));
    door4->setPos(Vec2f(12.0F,1.0F));
    door4->setTexture("Portals/portal_blue.png");
    m_objects.push_back(door4);
    //
    Door *door(new Door(1, Vec2f(2.01F)));
    door->setPos(Vec2f(9.0F,17.0F));
    door->setTexture("Portals/portal_green.png");
    m_objects.push_back(door);



    Interactive *inter(new Interactive());
    inter->setPos(Vec2f(5.0F, 11.0F));
    inter->setHealth(11);
    inter->setNonSolid();
    inter->setQuestState(Object::QuestStatus::QS_AVAILABLE);
    inter->setOnClickFunction(onclick);
    inter->getAI()->setEnabled();
    inter->getAI()->setMovementSpeed(6.0F);
    inter->getAI()->setDistanceVisibility(7.0F);
    inter->getAI()->setMinFollowDistance(3.0F);
    inter->setTexture("boss_bee.png");
    m_objects.push_back(inter);

    Interactive *inter1(new Interactive());
    inter1->setPos(Vec2f(5.0F, 5.0F));
    inter1->setHealth(11);
    inter1->setQuestState(Object::QuestStatus::QS_AVAILABLE);
    inter1->setOnClickFunction(onclick1);
    inter1->setName("John Doe");
    inter1->setTexture("hat-guy.png");
    m_objects.push_back(inter1);


    // Camera
    cam->setPos(Vec2f(4.0F, 4.0F));
    cam->setPosChanged();

    //m_cache = m_objects;
    //emit objVecResized();
    logEvent("SceneLoader0", EventLogger::LogType::LOG_TYPE_INFO, "Scene loaded successfuly!");
    m_loaded = true;
}

void Scene0::loadAmbientMusic(QMediaPlayer &amb_mus)
{
    // Audio
    amb_mus.setSource(QUrl("qrc:/src/assets/sounds/Red_Carpet_Wooden_Floor.mp3"));
}
