#include "game_engine.h"
#include "game_header.h"
#include <QTimer>
#include <iostream> // TODO: Remove after end debugging
#include "player.h"
#include "monster.h"
#include "projectile.h"
#include "interactive.h"
#include "door.h"
#include "bow.h"
#include "game_header.h"
#include "ray.h"
#include "dqmath.h"

#include "scene0.h"
#include "scene1.h"
#include "scene2.h"
#include "scene3.h"
#include "scene4.h"
#include "scene5.h"


#define ENGINE_LOOP_DISABLED
#define GE_OBJECTS_P m_objects
#define GE_OBJECTS (*m_objects)
#define GE_TILES (*m_tiles)
#define GE_TILES_P m_tiles

//MainEvent gh_main_event = ME_NONE;

const char *GameEngine::M_LOG_GAME_ENGINE = "GameEngine";
Camera *GameEngine::m_maincam = nullptr;
Time *GameEngine::m_time = nullptr;
Keyboard *GameEngine::m_keyboard = nullptr;
Mouse *GameEngine::m_mouse = nullptr;
GameState *GameEngine::m_gamestate = nullptr;
EventLogger *GameEngine::m_event_logger = nullptr;
Player *GameEngine::m_player = nullptr;
std::vector<Object*> *GameEngine::m_objects; // all the objects
QAudioOutput *GameEngine::m_aud_out_ambi = nullptr;
QAudioOutput *GameEngine::m_aud_out_pl = nullptr;
QMediaPlayer GameEngine::m_ambient_music;
QMediaPlayer GameEngine::m_player_debug;
std::vector<std::shared_ptr<BaseScene>> GameEngine::m_scenes;
size_t GameEngine::m_current_scene = 0;
bool GameEngine::m_debug_key_subtr = false;
bool GameEngine::m_debug_key_add = false;
bool GameEngine::m_debug_key_ctrl = false;
bool GameEngine::m_debug_key_escape = false;
bool GameEngine::m_debug_button_l = false;
bool GameEngine::m_debug_button_r = false;
bool GameEngine::m_debug_button_m = false;
tileGenerator GameEngine::m_generator;
std::vector<Tile*> *GameEngine::m_tiles = nullptr;
Quest *GameEngine::m_temp_quest = nullptr;
Quest *GameEngine::m_active_quest = nullptr;
std::vector<Quest*> GameEngine::m_quests;
Inventory *GameEngine::m_inventory/*(5, 5)*/; // TODO: Make shared_ptr if setup never called from QML
TextBox *GameEngine::m_textbox = nullptr;
// TODO: Maybe add shortcut directly to player? (std::shared_ptr<Player> m_player... player will be also part of object vector)
int GameEngine::m_window_width;
int GameEngine::m_window_height;
float GameEngine::m_previous_fixed_update; // TODO: Decide if it is necessary to put it here
QTimer *GameEngine::m_timer = nullptr;
//QKeyEvent *m_key_event;
bool GameEngine::m_init_success = false;
bool GameEngine::m_setup_enabled = true;
bool GameEngine::m_reset_enabled = false;
bool GameEngine::m_connected = false;
GameEngine *GameEngine::m_instance = nullptr;

// TODO: Refactor (IMPORTANT)
GameEngine::GameEngine(int argc, char *argv[], QQmlContext *qml_context, QObject *parent) : QObject(parent)
{
    try
    {
        if (init())
        {
            m_init_success = true;
            std::cout << "Game engine initialization succeeded!" << std::endl;
        }
        else
        {
            m_init_success = false;
            throw(m_init_success);
        }
    }
    catch (bool result)
    {
        std::cerr << "Game engine initialization failed!" << std::endl;
        std::cerr << "Init result: " << result << std::endl;
    }


    // Configuration for QML object access
    qml_context->setContextProperty("m_maincam", m_maincam);
    qmlRegisterType<Camera>("Camera", 1, 0, "Camera");
    qml_context->setContextProperty("m_keyboard", m_keyboard);
    qmlRegisterType<Keyboard>("Keyboard", 1, 0, "Keyboard");
    qml_context->setContextProperty("m_mouse", m_mouse);
    qmlRegisterType<Mouse>("Mouse", 1, 0, "Mouse");
    qml_context->setContextProperty("m_gamestate", m_gamestate);
    qmlRegisterType<GameState>("GameState", 1, 0, "GameState");
    qmlRegisterType<Object>("ObjQuestStatus", 1, 0, "ObjQuestStatus");
    qml_context->setContextProperty("m_textbox", m_textbox);
    qml_context->setContextProperty("generator", &m_generator);
    qml_context->setContextProperty("TILE_SIZE", gh::GH_DEFAULT_TILE_VISUAL_SIZE);
    qml_context->setContextProperty("m_inventory", m_inventory);
    //qml_context->setContextProperty("testpoint", &gh_test_point);

    if (argc)
    {
        // TODO: arg
        std::cout << "DEBUG: Argument (argc) count is-> " << argc << "." << std::endl;
        std::cout << "DEBUG: First argument (argv) is-> " << argv[0] << "." << std::endl;
        argv; // To get last argument do argv[argc - 1]
    }

    std::cout << "\n\n!!AUDIO WILL PLAY AFTER START!!\n" << std::endl;
}

GameEngine::~GameEngine()
{
    if (m_aud_out_ambi)
    {
        delete m_aud_out_ambi;
        m_aud_out_ambi = nullptr;
    }

    if (m_aud_out_pl)
    {
        delete m_aud_out_pl;
        m_aud_out_pl = nullptr;
    }
    m_maincam->destroy();
    m_maincam = nullptr;
    m_time->destroy();
    m_time = nullptr;
    m_keyboard->destroy();
    m_keyboard = nullptr;
    m_mouse->destroy();
    m_mouse = nullptr;
    m_gamestate->destroy();
    m_gamestate = nullptr;
    m_textbox->destroy();
    m_textbox = nullptr;
    m_inventory->destroy();
    m_inventory = nullptr;
    m_event_logger->closeLog();
    m_event_logger->destroy();
    m_event_logger = nullptr;
    reset();
    delete m_timer;
    logEvent(M_LOG_GAME_ENGINE, EventLogger::LogType::LOG_TYPE_INFO, "Shutting down!");
}

bool GameEngine::init() // TODO: Add checks to return if failed (if really necessary)
{
    m_window_width = gh::GH_SCREEN_W;
    //emit windowWidthSet();
    m_window_height = gh::GH_SCREEN_H;
    //emit windowHeightSet();
    *m_gamestate = GameState::State::GS_FIRST_INIT;

    // TODO: Refactor and move on appropriate place (especially the timer location on game (engine) launch)
    m_timer = new QTimer();

    m_aud_out_ambi = new QAudioOutput();
    m_aud_out_ambi->setVolume(0.7F);
    m_ambient_music.setLoops(-1); // Infinite (-1)
    m_ambient_music.setAudioOutput(m_aud_out_ambi);
    m_aud_out_pl = new QAudioOutput();

    //DEBUG
    m_player_debug.setSource(QUrl("qrc:/src/assets/sounds/hurt1.mp3"));
    m_player_debug.setAudioOutput(new QAudioOutput);
    // DEBUG
    m_player_debug.setAudioOutput(m_aud_out_pl);
    EventLogger::instantiate("Log");
    m_event_logger = EventLogger::getInstance();
    Camera::instantiate();
    m_maincam = Camera::getInstance();
    Time::instantiate();
    m_time = Time::getInstance();
    Keyboard::instantiate();
    m_keyboard = Keyboard::getInstance();
    Mouse::instantiate();
    m_mouse = Mouse::getInstance();
    GameState::instantiate();
    m_gamestate = GameState::getInstance();
    std::cout << "TextBox instantiate" << std::endl;
    TextBox::instantiate();
    m_textbox = TextBox::getInstance();
    std::cout << "TextBox saved" << std::endl;
    m_setup_enabled = true;
    Inventory::instantiate(gh::GH_INVENTORY_WIDTH, gh::GH_INVENTORY_HEIGHT);
    m_inventory = Inventory::getInstance();

    m_inventory->setup(7, 7);
    m_inventory->addItem(new Bow("weapon5.png"));
    std::cout << "Inv size: " << m_inventory->getInv().size() << std::endl;

    m_maincam->setBorderX(12.0F);
    m_maincam->setBorderY(8.0F);

    m_scenes.push_back(std::shared_ptr<Scene0>(new Scene0()));
    m_scenes.push_back(std::shared_ptr<Scene1>(new Scene1()));
    m_scenes.push_back(std::shared_ptr<Scene2>(new Scene2()));
    m_scenes.push_back(std::shared_ptr<Scene3>(new Scene3()));
    m_scenes.push_back(std::shared_ptr<Scene4>(new Scene4()));
    m_scenes.push_back(std::shared_ptr<Scene5>(new Scene5()));


    return true;
}

bool GameEngine::instantiate(int argc, char *argv[], QQmlContext *qml_context, QObject *parent)
{
    if (!m_instance)
    {
        m_instance = new GameEngine(argc, argv, qml_context, parent);
    }

    return m_init_success;
}

void GameEngine::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

GameEngine *GameEngine::getInstance()
{
    return m_instance;
}

void GameEngine::debugSceneLoader()
{
    return;
    // TODO: tilegenerator.h make
    if (m_keyboard->isPressed(Keyboard::KKeys::K_NUM0))
    {
        loadScene(0);
    }
    else if (m_keyboard->isPressed(Keyboard::KKeys::K_NUM1))
    {
        loadScene(1);
    }
}
#if 0
void GameEngine::objectSceneEraser()
{
    for (auto o : GE_OBJECTS)
    {
        delete o;
    }

    GE_OBJECTS.clear();
    m_player = nullptr;
    emit m_instance->playerModified();
    emit m_instance->objVecResized();
}
#endif
void GameEngine::questEraser()
{
    for (auto q : m_quests)
    {
        delete q;
        emit m_instance->questVecResized();
    }

    m_quests.clear();
    m_temp_quest = nullptr;
    m_active_quest = nullptr;
    emit m_instance->tempQuestModified();
    emit m_instance->activeQuestModified();
}

void GameEngine::loadScene(int id)
{
    m_ambient_music.stop();
    m_mouse->releaseAll();
    m_objects = nullptr;
    emit m_instance->objVecResized();

    if (!m_player)
    {
        m_player = new Player();
        emit m_instance->playerModified();
        std::cout << "Player does not exist!" << std::endl;
    }

    m_player->setTexture("sensei.png");

    // INFO: No vector out of range check
    std::cout << "Before scene isLoaded!" << std::endl;
    if (!m_scenes[id]->isLoaded())
    {
        std::cout << "Before scene load!" << std::endl;
        m_scenes[id]->initScene(m_player, m_maincam, m_tiles, m_generator);

        if (id == 0)
        {
            m_player->setPos(Vec2f(3.0F, 5.0F));
            (*m_scenes[id]->getContents()).push_back(m_player);
        }

        std::cout << "After scene load!" << std::endl;
    }
    else
    {
        m_generator.setMap(id); // do not mix ids. It would be better to have generator and scene loader as a single class
        GE_TILES_P = m_generator.getCppTiles();
    }

    std::cout << "Player status: " << m_player << std::endl;

    GE_OBJECTS_P = m_scenes[id]->getContents();
    m_scenes[id]->loadAmbientMusic(m_ambient_music);
    camChangeDetector();
    m_ambient_music.play();
    m_mouse->setCursor(Mouse::MCursors::C_CROSSHAIR); // TODO: Remove after weapon in hand detection added
    emit m_instance->objVecResized();
}

void GameEngine::camChangeDetector()
{
    if (m_maincam->posChanged())
    {
        // TODO: Decide if making m_tiles and m_tiles_mat to have two vectors for different operations
#ifdef TILE_SELF_RENDER
        for (auto t : m_tiles)
        {
            emit t->camPosChanged();
        }
#endif
        m_maincam->resetPosChanged();
        emit m_generator.cameraPosOrLevelOriginChanged();
    }
}

QVariant GameEngine::getObjects()
{
    if (m_objects)
    {
        return QVariant::fromValue((*m_objects));
    }

    return QVariant::fromValue(v_objects{});
}

QVariant GameEngine::getQuests()
{
    return QVariant::fromValue(m_quests);
}

QVariant GameEngine::getTempQuest()
{
    return QVariant::fromValue(m_temp_quest);
}

QVariant GameEngine::getActiveQuest()
{
    return QVariant::fromValue(m_active_quest);
}

QVariant GameEngine::getPlayer()
{
    return QVariant::fromValue(m_player);
}

int GameEngine::getQuestCount()
{
    return int(m_quests.size());
}

QVariant GameEngine::getObject(int index)
{
    return QVariant::fromValue(m_objects[index]);
}

int GameEngine::getWindowWidth()
{
    return m_window_width;
}

int GameEngine::getWindowHeight()
{
    return m_window_height;
}

// TODO: Refactor (IMPORTANT)
void GameEngine::setup()
{
    std::cout << "DEBUG: Game engine setup called!" << std::endl;

    if (!m_connected)
    {
        connect(m_timer,SIGNAL(timeout()),m_instance,SLOT(runFrame()));
        m_connected = true;
    }

    // DEBUG
    *m_gamestate = GameState::State::GS_FIRST_INIT;

    if (m_setup_enabled)
    {
        // INFO: If fixed_delta is 0.02 that means 50 per sec. Fixed_delta / 4 * 1000 will be 4 times faster for this code
        float temp_fixed_delta = gh::GH_FIXED_DELTA_TIME / 4.0F; // In s
        std::cout << "DEBUG: Before timer start!" << std::endl;
        m_timer->start(int(temp_fixed_delta * 1000.0F)); // In ms
        std::cout << "DEBUG: After timer start!" << std::endl;
        m_time->fixedDeltaTime() = gh::GH_FIXED_DELTA_TIME;
        // set default values
        //TODO: Some preparation
        m_previous_fixed_update = 0.0F;
        m_setup_enabled = false; // disables setup (only reset can enable setup again)
        m_reset_enabled = true;
        m_time->startFrame();

        std::cout << "\n\n!!VOLUME CONTROLS: NUM- AND NUM+!!\n" << std::endl;
        std::cout << "\n\n!!VOLUME CONTROLS: NUM- AND NUM+!!\n" << std::endl;

        return;
    }

    std::cout << "DEBUG: ... but setup was not allowed!" << std::endl;
}

void GameEngine::reset()
{
    std::cout << "DEBUG: Game engine reset called!" << std::endl;
    if (m_reset_enabled)
    {
        m_reset_enabled = false;
        // TODO: Reset values here (clear, delete etc.)
        *m_gamestate = GameState::State::GS_RESET;
        m_timer->stop();
        m_ambient_music.stop();
        m_player_debug.stop();
        delete m_player;
        m_player = nullptr;
        emit m_instance->playerModified();
        //objectSceneEraser();
        m_objects = nullptr;
        emit m_instance->objVecResized();
        m_inventory->setup(7, 7);
        m_inventory->addItem(new Bow("weapon5.png")); // DEBUG

        for (auto s: m_scenes)
        {
            s->clearContents();
        }

        questEraser();

        m_setup_enabled = true;
        std::cout << "Reset finished!" << std::endl;

        return;
    }

    std::cout << "But reset was not allowed! (Cannot call reset twice... still DEBUG)" << std::endl;
}

void GameEngine::setGameState(const GameState::State state)
{
    *m_gamestate = state;
}

void GameEngine::switchCursor()
{
    // if holding weapon m_mouse->setCursor(Mouse::MCursors::C_CROSSHAIR);
    // if something else and if correct state change cursor to specific type
    m_mouse->setCursor(Mouse::MCursors::C_CROSSHAIR);
}

int GameEngine::runFrame()
{
    m_time->endFrame(); // End frame was moved here because it takes a while to call runFrame again
    m_time->startFrame();
    //if (GH_MAIN_EVENT == ME_QUIT)
    //    break;
    m_previous_fixed_update += m_time->deltaTime();
    //TODO: If error handler throws an error then return 1 or something else than 0 (number determines type of error)
    gameState();

    return 0; // TODO: Remove because QML can handle things and this function is not called in main manually
}

void GameEngine::gameState()
{
    // TODO: Add more states if needed (or remove useless... and merge similar)
    switch (m_gamestate->getState())
    {
        case GameState::State::GS_FIRST_INIT:
        *m_gamestate = GameState::State::GS_LOAD_SCENE;
        break;
        case GameState::State::GS_LOAD_SCENE: // aka load level (current world)
        runLoadScene();
        break;
        case GameState::State::GS_RUN_SCENE:  // main game logic
        runScene();
        break;
        case GameState::State::GS_LOAD_CUTSCENE:
        runLoadCutscene();
        break;
        case GameState::State::GS_RUN_CUTSCENE: // Loads scene and then animations
        runCutscene();
        break;
        case GameState::State::GS_MAIN_MENU:
        runMainMenu();
        break;
        case GameState::State::GS_PAUSE_MENU:
        runPauseMenu();
        break;
        case GameState::State::GS_LOAD_MENU:
        break;
        case GameState::State::GS_SAVE_MENU:
        break;
        case GameState::State::GS_SETTINGS_MENU:
        break;
        case GameState::State::GS_CREDITS_MENU:
        break;
        case GameState::State::GS_INVENTORY:
        runInventory(); // will need flip-flop for [ESC] key if used (key [I] mandatory)
        // runScene();
        // runScene only if we need to run game in the background while in inventory
        // and if so then olso it is needed to disable mouse click in Scene and enable it in Inventory {} only
        break;
        case GameState::State::GS_TEXTBOX_POPUP:
        runTextboxPopup(); // gets activated when clicked on something interactive which causes generation of messages
        break;
        case GameState::State::GS_QUEST_POPUP:
        runQuestPopup();
        // TODO: Add popup text at the bottom plus possible window on top like inventory
        break;
        case GameState::State::GS_QUEST_LIST:
        runQuestList();
        runScene();
        break;
        case GameState::State::GS_GAME_OVER: // DEBUG
       // setup();
        break;
        case GameState::State::GS_PLAYER_DEAD: // DEBUG
        reset();
        m_gamestate->setState(GameState::State::GS_GAME_OVER);
        break;
        case GameState::State::GS_RESET:
        break;
        default:
        // TODO: FATAL ERROR: Unknown game state... QUIT (or clear and reset or try to set default state)
        break;
    }

    // TODO: If inventory gamestate is active (in case:) press [ESC] or [I] to go back to run scene gamestate

    // TODO: PAUSE_MENU, LOAD_MENU, SAVE_MENU and similar menus will be controlled from QML
    //       add something like GS_PAUSED when in menus. Only things like INVENTORY and similar will keep scene running (if wanted as a feature)
    //       so maybe a GameSubState will be needed? (or just add, if inventory_is_open then render inventory too... but player movement must be disabled)
}

void GameEngine::runScene()
{
    if (m_previous_fixed_update >= gh::GH_FIXED_DELTA_TIME) // fixed_timer += deltaTime > (1 / FIXED_UPDATE) Example: 0.02 for 50 times per second
    {
        m_previous_fixed_update = 0.0F;
        fixedUpdate();
    }

    // How to do interrupts?
    //debugSceneLoader();
    eventEnterPauseMenu();
    eventEnterInventory();
    eventOpenQuestList();
    eventMouseInteract(); // DEBUG

    if (m_keyboard->isPressed(Keyboard::KKeys::K_LCONTROL) && !m_debug_key_ctrl)
    {
        m_debug_key_ctrl = true;
        std::cout << "Ctrl!" << std::endl;
        //m_player_debug.setPosition(0);
        //m_player_debug.play();
    }
    else if (!m_keyboard->isPressed(Keyboard::KKeys::K_LCONTROL) && m_debug_key_ctrl)
    {
        m_debug_key_ctrl = false;
    }

    // DEBUG: Ambient volume
    if (m_keyboard->isPressed(Keyboard::KKeys::K_SUBTR) && !m_debug_key_subtr)
    {
        m_debug_key_subtr = true;

        if (m_aud_out_ambi->volume() > 0.0F)
        {
            m_aud_out_ambi->setVolume(m_aud_out_ambi->volume() - 0.05F);
        }
    }
    else if (!m_keyboard->isPressed(Keyboard::KKeys::K_SUBTR) && m_debug_key_subtr)
    {
        m_debug_key_subtr = false;
    }

    if (m_keyboard->isPressed(Keyboard::KKeys::K_ADD) && !m_debug_key_add)
    {
        m_debug_key_add = true;

        if (m_aud_out_ambi->volume() < 1.0F)
        {
            m_aud_out_ambi->setVolume(m_aud_out_ambi->volume() + 0.05F);
        }
    }
    else if (!m_keyboard->isPressed(Keyboard::KKeys::K_ADD) && m_debug_key_add)
    {
        m_debug_key_add = false;
    }
    // DEBUG: Ambient volume

    update();
}

// INFO: for inputs etc.
void GameEngine::update()
{
    for (auto o : GE_OBJECTS)
    {
        o->update();
        Physical *phys = o->asPhysical();
        if (!phys) { continue; }
        Entity *ent = phys->asEntity();
        if (!ent) { continue; }
        // Handles projectile input
        Projectile *proj = ent->getProjectile();
        if (!proj) { continue; }
        GE_OBJECTS.push_back(proj);
        emit m_instance->objVecResized();
    }

    // If cam pos changed, send signals to tiles
    camChangeDetector();
}
// INFO: for physics and real time behavior
// TODO: Refactor (IMPORTANT)
void GameEngine::fixedUpdate()
{
    for (int i = 0; i < int(GE_OBJECTS.size()); i++)
    {
        GE_OBJECTS[i]->fixedUpdate();
    }

    objectVsObjectInteractions();
    objectVsTileInteractions();

    for (auto o : GE_OBJECTS)
    {
        emit o->posChanged();
    }
}

bool GameEngine::destroyProjectileOnDistanceReached(Object *obj, int &i)
{
    Physical *phys = obj->asPhysical();
    if (!phys) { return false; }
    Entity *entity = phys->asEntity();
    if (!entity) { return false; }
    Projectile *proj = entity->asProjectile();
    if (!proj) { return false; }

    if (proj->hasReachedEnd())
    {
        delete phys;
        GE_OBJECTS.erase(GE_OBJECTS.begin() + i);
        i--;
        emit m_instance->objVecResized();
        return true;
    }

    return false;
}

// TODO: Refactor
void GameEngine::objectVsObjectInteractions()
{
    for (int i = 0; i < int(GE_OBJECTS.size()); i++)
    {
        destroyProjectileOnDistanceReached(GE_OBJECTS[i], i);
        eventMouseClickOnObject(GE_OBJECTS[i]);

        if (i < 0) { break; }
        //Physical *phys_i = dynamic_cast<Physical*>(m_objects[i]);
        //if (!phys_i) { continue; }

        for (int j = 0; j < int(GE_OBJECTS.size()); j++)
        {
            Physical *phys_i = GE_OBJECTS[i]->asPhysical();
            if (!phys_i) { break; }
            if (j < 0) { break; }
            if (i == j) { continue; }
            Physical *phys_j = GE_OBJECTS[j]->asPhysical();

            if (phys_j)
            {
#if 0
                phys_i->m_debug_in_collision = false;
                emit phys_i->debugCollisionChanged();
                phys_j->m_debug_in_collision = false;
                emit phys_j->debugCollisionChanged();
#endif
                physicalVsPhysical(phys_i, phys_j, i, j);
            }

        }
    }
}

//#define FIXING_AABB_COLLISIONS
// TODO: Refactor
void GameEngine::objectVsTileInteractions()
{
    Vec2f contact_point;
    Vec2f contact_normal;
    Vec2f push;
    float hit_near;
    float hit_far;
    // TODO: to be resolved
    std::vector<std::pair<int, std::vector<std::pair<int, float>>>> obj_and_tiles_collided;
    std::vector<int> crop;

    for (int i = 0; i < int(GE_OBJECTS.size()); i++)
    {
        bool phys_collided = false;
        Physical *physical_i = GE_OBJECTS[i]->asPhysical();
        if (!physical_i) { continue; }
        Vec2f borders(3.0F);
        crop = DQMath::cropSurroundings(GE_TILES.size(), m_generator.getMapWidth(), m_generator.getMapHeight(), physical_i->getPos(), borders, gh::GH_DEFAULT_TILE_SIZE);
        if (!GE_TILES.size())
        { continue; }
        std::vector<std::pair<int, float>> tiles_collided;

        for (auto j : crop)
        {
            Tile *tile_j = GE_TILES[j];
            if (!tile_j) { continue; }
            if (tile_j->isTouchable())
            {
                Entity *entity = physical_i->asEntity();
                Projectile *proj = nullptr;

                if (entity)
                {
                    proj = entity->asProjectile();
                }

                if (!proj)
                {
#ifdef FIXING_AABB_COLLISIONS
                    if (DQMath::aabbDynamicCollision(tile_j->m_aabb, physical_i, prev_pos[i], contact_point, contact_normal, hit_near, hit_far))
                    {
                        phys_collided = true;
                        tiles_collided.push_back({j, hit_near});
                    }
#else
                    if (tile_j->m_aabb.calcDynamicCollision(physical_i->getAABB(), physical_i->getPrevPos(), contact_point, contact_normal, hit_near, hit_far))
                    {
                        phys_collided = true;
                        tiles_collided.push_back({j, hit_near});
                    }
#endif
                    continue;
                }

                // Removes projectile if collided with tile
                if (tile_j->m_aabb.isColliding(physical_i->getAABB()))
                {
                    delete physical_i;
                    GE_OBJECTS.erase(GE_OBJECTS.begin() + i);
                    i--;
                    emit m_instance->objVecResized();
                    break;
                }
            }

        }

        if (!phys_collided) { continue; }
        obj_and_tiles_collided.push_back({i, tiles_collided});
    }

    for (int i = 0; i < int(obj_and_tiles_collided.size()); i++)
    {
        std::sort(obj_and_tiles_collided[i].second.begin(), obj_and_tiles_collided[i].second.end(), [](const std::pair<int, float> &a, const std::pair<int, float> &b)
                  {
                      return a.second < b.second;
                  });
    }

    Ray ray;

    for (int i = 0; i < int(obj_and_tiles_collided.size()); i++)
    {
        int obj_index = obj_and_tiles_collided[i].first;
        Physical *physical = GE_OBJECTS[obj_index]->asPhysical();
        ray.m_origin = physical->getPrevPos();
        ray.m_end = physical->getPos();

        for (auto ct : obj_and_tiles_collided[i].second)
        {
            //push = DQMath::resolveStaticVsPhysicalCollision(physical, GE_TILES[ct.first]->m_aabb);
            GE_TILES[ct.first]->m_aabb.calcDynamicCollision(physical->getAABB(), physical->getPrevPos(), contact_point, contact_normal, hit_near, hit_far);
            //ray.getCollisionPoint(ct.second);
            push = contact_normal * physical->getVelocity().getAbs() * gh::GH_FIXED_DELTA_TIME;
#ifdef CRAZY_PHYSICS
            physical->onCollide(nullptr, push);
#else
            physical->move(push);
#endif
        }
    }
}

void GameEngine::physicalVsPhysical(Physical *phys_i, Physical *phys_j, int &i, int &j)
{
    if (phys_i->isSolid() && phys_j->isSolid()) // TODO: Maybe add isSleeping too to prevent movement instead of going through?
    {
        if (phys_i->isAABBColliding(*phys_j))
        {
#if 0
            phys_i->m_debug_in_collision = true;
            emit phys_i->debugCollisionChanged();
            phys_j->m_debug_in_collision = true;
            emit phys_j->debugCollisionChanged();
#endif
            Vec2f contact_point;
            Vec2f contact_normal;
            Vec2f push;
            float hit_near;
            float hit_far;
            phys_i->getAABB().calcDynamicCollision(phys_j->getAABB(), phys_j->getPrevPos(), contact_point, contact_normal, hit_near, hit_far);
            // TODO: Fix on collide push. This causes objects going out of bounds.
            //       Instead use velocity only... similar to Minecraft where entities won't avoid collision but apply force and calculate velocity.
            push = contact_normal.negated() * phys_j->getVelocity().getAbs() * gh::GH_FIXED_DELTA_TIME;
            phys_i->onCollide(phys_j, push);
        }
    }

    Door *door_j = phys_j->asDoor();

    if (door_j)
    {
        physicalVsDoor(phys_i, door_j, i, j);
    }

    Entity *ent_i = phys_i->asEntity();
    Entity *ent_j = phys_j->asEntity();
    Item *item_j = phys_j->asItem();

    if (ent_i && item_j)
    {
        entityVsItem(ent_i, item_j, i, j);
    }

    if(ent_i && ent_j)
    {
        entityVsEntity(ent_i, ent_j, i, j);
    }
}

void GameEngine::physicalVsDoor(Physical *phys_i, Door *door_j, int &i, int &j)
{
    if (!door_j->isLocked())
    {
        if (phys_i->isAABBColliding(door_j->getAABB())) // TODO: Fix and move to function
        {
            size_t level_id = door_j->getLevelID();

            if (!moveObjectToScene(phys_i, int(level_id), i))
            { return; }

            phys_i->setPos(door_j->getTargetLocation());
            bool is_player = m_player == phys_i;
            std::cout << "Object moved through door!" << std::endl;
            std::cout << "Object erased from current scene!" << std::endl;
            i--;
            if (j > i) { j--; }

            if (is_player) // if player switch level (scene objects)
            {
                loadScene(level_id);
                std::cout << "Player moved to another level!" << std::endl;
                Camera::setPos(door_j->getTargetLocation());
                emit Camera::setPosChanged();
                i = 0;
                j = 0;
                // TODO: Switch tile too (using generator setMap and getCppTiles)
            }
        }

        return;
    }

    if (phys_i->isAABBColliding(door_j->getAABB()))
    {
        Vec2f contact_point;
        Vec2f contact_normal;
        Vec2f push;
        float hit_near;
        float hit_far;
        phys_i->getAABB().calcDynamicCollision(door_j->getAABB(), door_j->getPrevPos(), contact_point, contact_normal, hit_near, hit_far);
        // TODO: Fix on collide push. This causes objects going out of bounds.
        //       Instead use velocity only... similar to Minecraft where entities won't avoid collision but apply force and calculate velocity.
        push = contact_normal.negated() * door_j->getVelocity().getAbs() * gh::GH_FIXED_DELTA_TIME;
        phys_i->onCollide(door_j, push); // Push away from door
    }
}

// always only one way because iterator will make the swap for tihs function
void GameEngine::entityVsEntity(Entity *ent_i, Entity *ent_j, int &i, int &j)
{
    // DEBUG
    //Monster *mon = ent_i->asMonster();

    //if (mon)
    //{
        if (ent_j->getName() == "player")
        {
            //mon->fixedUpdateAI(ent_j);
            ent_i->getAI()->followObject(ent_i, ent_j);
        }
    //}
    // DEBUG

    entityVsEntityAttack(ent_i, ent_j, i, j);

    Projectile *proj_j = ent_j->asProjectile();

    if (proj_j)
    {
        entityVsProjectile(ent_i, proj_j, i, j);
    }
}

void GameEngine::entityVsEntityAttack(Entity *ent_i, Entity *ent_j, int &i, int &j)
{
    if (ent_j->isAABBColliding(ent_i->getAABB()))
    {
        if (ent_i->getName() == "player") // INFI: simplified (not enough time)
        {
            ent_j->getAI()->actionAttack(ent_j, ent_i); // ent_j will hurt ent_i

            if (ent_i->getHealth() <= 0)
            {
                eventQuestActionOnObjectInteract(ent_i, EntityActions::EA_KILL);
                std::cout << "\n\nPlayer is dead! GAME OVER screen here!\n" << std::endl;
                m_gamestate->setState(GameState::State::GS_PLAYER_DEAD);
                //delete GE_OBJECTS[i];
                //ent_i = nullptr;
                //GE_OBJECTS.erase(GE_OBJECTS.begin() + i);
                //i--;
                //if (j > i) { j--; } // if second object j has bigger id then subtract j too
                //emit m_instance->objVecResized();
            }
        }
    }
}

void GameEngine::entityVsProjectile(Entity *ent_i, Projectile *proj_j, int &i, int &j)
{
    if (!ent_i->isAABBColliding(proj_j->getAABB()))
    { return; }

    // Health action
    std::cout << "Entity health before: " << ent_i->getHealth() << std::endl;
    if ((proj_j->getOwner() == "player" && ent_i->getName() == "player") || (proj_j->getOwner() == "game_engine" && ent_i->getName() == "player")) // DEBUG
    { return; }

    proj_j->actionAttack(ent_i);
    std::cout << "Entity health after: " << ent_i->getHealth() << std::endl;

    if (ent_i->getHealth() <= 0)
    {
        eventQuestActionOnObjectInteract(ent_i, EntityActions::EA_KILL);
        std::cout << "Entity \'" << ent_i->getName() << "\' is dead. Removing! " << std::endl;
        std::cout << "Cause:\nKilled by \'" << proj_j->getName() << "\' of owner \'" << proj_j->getOwner() << "\'!" << std::endl;
        Item *temp = ent_i->dropHoldingItem();

        if (temp)
        {
            temp->setPos(ent_i->getPos());
            GE_OBJECTS.push_back(temp);
        }

        delete GE_OBJECTS[i];
        ent_i = nullptr;
        GE_OBJECTS.erase(GE_OBJECTS.begin() + i);
        i--;
        if (j > i) { j--; } // if second object j has bigger id then subtract j too
        emit m_instance->objVecResized();
    }

    // If is a projectile
    delete GE_OBJECTS[j];
    proj_j = nullptr;
    GE_OBJECTS.erase(GE_OBJECTS.begin() + j);
    j--;
    if (i > j) { i--; } // INFO: One of these two checks is maybe useless
    emit m_instance->objVecResized();
}

void GameEngine::entityVsItem(Entity *ent_i, Item *item_j, int &i, int &j)
{
    if (ent_i->getName() == "player")
    {
        Ray ray(ent_i->getAABB().getCenter(), item_j->getAABB().getCenter());

        if (ray.getDistance() > 1.5F)
        { return; }

        item_j->addForce(ray.getDirection().normalized().negated() * 8.0F, Physical::ForceMode::VelocityChange);

        if (ray.getDistance() > 0.4F)
        { return; }
        if (!m_inventory->addItem(item_j))
        { return; }

        GE_OBJECTS.erase((GE_OBJECTS.begin() + j));
        emit m_instance->objVecResized();
        j--;
        if (i > j) { i--; }
    }
}

void GameEngine::DEBUGResetTileCollisionVisibility()
{
    for (auto t : *m_generator.getCppTiles())
    {
        t->m_debug_in_collision = false;
        emit t->debugCollisionChanged();
        t->m_debug_is_clicked = false;
        emit t->debugClickedChanged();
    }
}

void GameEngine::DEBUGShowTileVsMouseCollision(Tile *tile, Physical *phys)
{
    // DEBUG: Test available mouse tiles
    Entity *entity0 = phys->asEntity();

    if (entity0)
    {
        Player *player = entity0->asPlayer();

        if (player)
        {
            if (player->getName() == "player")
            {
                Vec2f mouse_tiled_pos = m_mouse->getTileTransformedPos();

                if (tile->m_aabb.isPointColliding(mouse_tiled_pos))
                {
                    if (!m_mouse->isPressed(Mouse::MButtons::B_LBUTTON))
                    {
                        tile->m_debug_in_collision = true;
                        emit tile->debugCollisionChanged();
                    }
                    else
                    {
                        tile->m_debug_is_clicked = true;
                        emit tile->debugClickedChanged();
                    }
                }
            }
        }
    }
    // DEBUG: Test available mouse tiles
}

void GameEngine::eventEnterPauseMenu()
{
    if (m_gamestate->getState() == GameState::State::GS_RUN_SCENE)
    {
        if (m_keyboard->isClicked(Keyboard::KKeys::K_ESCAPE))
        {
            *m_gamestate = GameState::State::GS_PAUSE_MENU;
            emit m_gamestate->gameStateChanged();
            m_mouse->setCursor(Mouse::MCursors::C_DEFAULT);
            m_keyboard->releaseAll();
        }
    }
}

void GameEngine::eventEnterInventory()
{
    if (m_keyboard->isPressed(Keyboard::KKeys::K_I))
    {
        *m_gamestate = GameState::State::GS_INVENTORY;
        emit m_gamestate->gameStateChanged();
        m_mouse->setCursor(Mouse::MCursors::C_DEFAULT);
        m_keyboard->releaseAll();
    }
}

void GameEngine::eventOpenQuestList()
{
    if (m_keyboard->isClicked(Keyboard::KKeys::K_K))
    {
        *m_gamestate = GameState::State::GS_QUEST_LIST;
        emit m_gamestate->gameStateChanged();
    }
}

void GameEngine::eventMouseInteract()
{
    if (m_mouse->isClicked(Mouse::MButtons::B_LBUTTON))
    {
        Vec2f player_center = m_player->getAABB().getCenter() - 0.3F;
        m_debug_button_l = true;
        Ray ray(player_center, m_mouse->getTileTransformedPos());
        Projectile *proj = new Projectile(player_center + ray.getDirection().normalized(), 5.0F);
        proj->setDrag(0.0F);
        proj->setVelocity(ray.getDirection().normalized() * gh::GH_DEFAULT_PROJECTILE_SPD_MUL);
        proj->setTexture("projectile.png");
        proj->setOwner("game_engine"); // DEBUG
        GE_OBJECTS.push_back(proj);
        emit m_instance->objVecResized();
    }
}

void GameEngine::eventMouseClickOnObject(Object *obj)
{
    Physical *phys = obj->asPhysical();
    if (!phys)
    { return; }

    Entity *ent = phys->asEntity();
    if (!ent)
    { return ;}

    Interactive *inter = ent->asInteractive();
    if(!inter)
    { return; }

    Vec2f mouse_tiled_pos = m_mouse->getTileTransformedPos();
    if(!inter->getAABB().isPointColliding(mouse_tiled_pos))
    { return; }

    if(!(m_mouse->isPressed(Mouse::MButtons::B_RBUTTON) || m_keyboard->isPressed(Keyboard::KKeys::K_E)))
    { return; }

    if (!m_player)
    { return; }

    if ((inter->getPos() - m_player->getPos()).mag() > gh::GH_MAX_DISTANCE_FOR_CLICKABLE_OBJECTS)
    { return; }

    inter->onCliced();
    std::cout << "Clicked on interactive entity!" << std::endl;

    if (m_temp_quest)
    {
        std::cout << "Has quest!" << std::endl;
    }
    else
    {
        std::cout << "Has no quest!" << std::endl;
    }
}

// TODO: When throwing away don't forget to check with all items in inventory
// TODO: When completing quest don't forget to iterate through all remaining quests after quest deletion to disable prepared for quests with the same quest target name (when not object pointer)
void GameEngine::eventQuestActionOnObjectInteract(Object *object, EntityActions action)
{
    for (int i = 0; i < int(m_quests.size()); ++i)
    {
        if (m_quests[i]->isSourceObject(object)) // If interaction with quest source object
        {
            switch (action)
            {
            case EntityActions::EA_TALK: // Means click on object
                if (m_quests[i]->isPrepared()) // Success
                {
                    std::cout << "QUEST ACTION p_obj: Killed source "  + object->getName() + "! SUCCESS" << std::endl;
                    Object *price = m_quests[i]->getPrice();
                    // TODO: Add to inventory (if inventory full drop on ground close to player)
                    //       Remove object/item from inventory if quest is related to bringing an item
                }
                // No break or return because it will delete quest afterwards
            case EntityActions::EA_KILL: // Fail
                std::cout << "QUEST ACTION p_obj: Killed source "  + object->getName() + "! FAIL" << std::endl;
                disableActiveQuest();
                delete m_quests[i];
                m_quests.erase(m_quests.begin() + i);
                emit m_instance->questVecResized();
                return;
            default:
                return;
            }
        }

        if (m_quests[i]->isTargetObjectPresent()) // if has object pointer as target
        {
            if (!m_quests[i]->isRequiredObject(object))
            { continue; }

            switch (action)
            {
            case EntityActions::EA_TALK: // Means click on object
                if (m_quests[i]->actionMatch(Quest::QType::QT_TALK))
                {
                    std::cout << "QUEST ACTION p_obj: Talked to requested entity "  + object->getName() + "!" << std::endl;
                    m_quests[i]->setPrepared();
                }
                return;
            case EntityActions::EA_KILL:
                if (m_quests[i]->actionMatch(Quest::QType::QT_KILL))
                {
                    std::cout << "QUEST ACTION p_obj: Killed requested entity "  + object->getName() + "!" << std::endl;
                    m_quests[i]->setPrepared();
                }
                // TODO: Quest fail
                std::cout << "QUEST ACTION p_obj: Killed " + object->getName() + " which wasn't meant to be killed! (FAIL)" << std::endl;
                disableActiveQuest();
                delete m_quests[i];
                m_quests.erase(m_quests.begin() + i);
                emit m_instance->questVecResized();
                return;
            case EntityActions::EA_PICK_UP:
                if (m_quests[i]->actionMatch(Quest::QType::QT_BRING))
                {
                    std::cout << "QUEST ACTION p_obj: Acquired requested item "  + object->getName() + "!" << std::endl;
                    m_quests[i]->setPrepared();
                }
                return;
            case EntityActions::EA_THROW_AWAY:
                if (m_quests[i]->actionMatch(Quest::QType::QT_BRING))
                {
                    std::cout << "QUEST ACTION p_obj: Thrown away requested item "  + object->getName() + "!" << std::endl;
                    m_quests[i]->setNonPrepared();
                }
                return;
            case EntityActions::EA_USE:
                if (m_quests[i]->actionMatch(Quest::QType::QT_BRING))
                {
                    std::cout << "QUEST ACTION p_obj: Used requested item "  + object->getName() + "!" << std::endl;
                    m_quests[i]->setNonPrepared();
                }
                return;
            default:
                // ERROR: Exception
                return;
            }

            continue; // TODO: Remove?
        }

        // if has no object pointer as target but only name instead (name for things like items. You could kill an item but if there are multiple items with the same name then it is fine.)
        std::string object_name = object->getName();

        if (m_quests[i]->isRequiredObject(object_name))
        {
            switch (action)
            {
            case EntityActions::EA_PICK_UP:
                if (m_quests[i]->actionMatch(Quest::QType::QT_BRING))
                {
                    std::cout << "QUEST ACTION name: Acquired requested item "  + object->getName() + "!" << std::endl;
                    m_quests[i]->setPrepared();
                }
                continue;
            case EntityActions::EA_THROW_AWAY:
                if (m_quests[i]->actionMatch(Quest::QType::QT_BRING))
                {
                    std::cout << "QUEST ACTION name: Thrown away requested item "  + object->getName() + "!" << std::endl;
                    m_quests[i]->setNonPrepared();
                }
                continue;
            case EntityActions::EA_USE:
                if (m_quests[i]->actionMatch(Quest::QType::QT_BRING))
                {
                    std::cout << "QUEST ACTION name: Used requested item "  + object->getName() + "!" << std::endl;
                    m_quests[i]->setNonPrepared();
                }
                continue;
            default:
                continue;
            }
        }
    }
}

bool GameEngine::moveObjectToScene(Object *obj, int scene_id, int obj_id)
{
    if (m_scenes.size())
    {
        if (scene_id >= 0 && scene_id < int(m_scenes.size()))
        {
            GE_OBJECTS.erase(GE_OBJECTS.begin() + obj_id);
            emit m_instance->objVecResized();
            m_scenes[scene_id]->getContents()->push_back(obj);
            std::cout << "Count of destination objects: " << (*m_scenes[scene_id]->getContents()).size() << std::endl;

            return true;
        }
    }

    return false;
}

void GameEngine::runLoadScene()
{
    std::cout << "runLoadScene() called!" << std::endl;
    loadScene(m_current_scene); // vector of scenes
#if 0
    if (m_scenes[m_current_scene]->hasCutscene())
    {
        *m_gamestate = GameState::State::GS_LOAD_CUTSCENE; // or GS_LOAD_CUTSCENE
        return;
    }
#endif
    m_gamestate->setState(GameState::State::GS_RUN_SCENE);
    // TODO: If scene has initial cutscene set gamestate to load cutscene and then disable for this scene forever
}

void GameEngine::runLoadCutscene()
{
    //m_scenes[m_current_scene]->loadCutscene(); // or loadCutScene(m_cutscene_id); // vector of cutscenes
    *m_gamestate = GameState::State::GS_RUN_CUTSCENE;
}

void GameEngine::runCutscene()
{
    // m_cutscenes[m_cutscene_id]->runFrame();
    // if (m_cutscenes[m_cutscene_id]->isFinished())
    // { *m_gamestate = GameState::GS_RUN_SCENE; } // exits cutscene

    //*m_gamestate = GameState::State::GS_RUN_SCENE; // TODO: Call this from cutscene if cutscene is finished
}

void GameEngine::runMainMenu()
{

}

void GameEngine::runPauseMenu()
{
    if (m_keyboard->isPressed(Keyboard::KKeys::K_ESCAPE))
    {
        *m_gamestate = GameState::State::GS_RUN_SCENE;
        emit m_gamestate->gameStateChanged();
        m_mouse->setCursor(Mouse::MCursors::C_CROSSHAIR);
        m_keyboard->releaseAll();
    }
}

void GameEngine::runInventory()
{
    if (m_keyboard->isPressed(Keyboard::KKeys::K_I) || m_keyboard->isPressed(Keyboard::KKeys::K_ESCAPE))
    {
        *m_gamestate = GameState::State::GS_RUN_SCENE;
        emit m_gamestate->gameStateChanged();
        m_mouse->setCursor(Mouse::MCursors::C_CROSSHAIR);
        m_keyboard->releaseAll();
    }
    // INFO: temporary debug solution

}

void GameEngine::runTextboxPopup()
{
    if (m_keyboard->isClicked(Keyboard::KKeys::K_RETURN) || m_mouse->isClicked(Mouse::MButtons::B_LBUTTON))
    {
        m_textbox->nextMessage();

        if (m_textbox->finishedReading())
        {
            *m_gamestate = GameState::State::GS_RUN_SCENE;
            m_mouse->setCursor(Mouse::MCursors::C_CROSSHAIR);
            m_keyboard->releaseAll();
            emit m_gamestate->gameStateChanged();
            m_textbox->reset();
            return;
        }
    }
}

void GameEngine::runQuestPopup()
{
    if (m_temp_quest) // Preview
    { return; }

    if (m_keyboard->isClicked(Keyboard::KKeys::K_RETURN))
    {
        claimQuest();
        *m_gamestate = GameState::State::GS_RUN_SCENE;
        emit m_gamestate->gameStateChanged();
        m_mouse->setCursor(Mouse::MCursors::C_CROSSHAIR);
        m_keyboard->releaseAll();
    }
}

void GameEngine::runQuestList()
{
    if (m_keyboard->isClicked(Keyboard::KKeys::K_K) || m_keyboard->isClicked(Keyboard::KKeys::K_ESCAPE))
    {
        *m_gamestate = GameState::State::GS_RUN_SCENE;
        emit m_gamestate->gameStateChanged();
        m_mouse->setCursor(Mouse::MCursors::C_CROSSHAIR);
    }
}

void GameEngine::enableQuestPreview(int id)
{
    m_temp_quest = m_quests[id];
    m_temp_quest->enablePreview();
    emit m_instance->tempQuestModified();
}

void GameEngine::disableQuestPreview()
{
    m_temp_quest->disablePreview();
    m_temp_quest = nullptr;
    emit m_instance->tempQuestModified();
}

void GameEngine::disableQuestPreviews()
{
    for (auto q : m_quests)
    {
        q->disablePreview();
    }
}

void GameEngine::setActiveQuest(int id)
{
    if (m_active_quest)
    { m_active_quest->setInactive(); }
    m_active_quest = m_quests[id];
    m_active_quest->setActive();
    emit m_instance->activeQuestModified();
}

void GameEngine::disableActiveQuest()
{
    if (m_active_quest)
    { m_active_quest->setInactive(); }

    m_active_quest = nullptr;
    emit m_instance->activeQuestModified();
}

void GameEngine::setAllQuestsAsInactive()
{
    for (auto q : m_quests)
    {
        q->setInactive();
    }
}

void GameEngine::addObject(Object *obj)
{
    GE_OBJECTS.push_back(obj);
    emit m_instance->objVecResized();
}

void GameEngine::newQuest(Quest *quest)
{
    disableActiveQuest();
    m_temp_quest = quest;
    emit m_instance->tempQuestModified();
}

void GameEngine::claimQuest()
{
    //if (!m_temp_quest->isClaimed())
    //{
        setAllQuestsAsInactive();
        m_temp_quest->setAsClaimed();
        m_quests.push_back(m_temp_quest);
        m_active_quest = m_temp_quest;
        m_temp_quest = nullptr;
        emit m_instance->questVecResized();
        emit m_instance->activeQuestModified();
        emit m_instance->tempQuestModified();
    //}
}

void GameEngine::declineQuest()
{
    delete m_temp_quest;
    m_temp_quest = nullptr;
    emit m_instance->tempQuestModified();
}

void GameEngine::completeQuest(int id)
{
    // TODO: If has item, push_back item to inventory (if inventory full push_back to Object vector on ground close to player)... or quest.onCompleted() with lambda?
    delete m_quests[id];
    m_quests.erase(m_quests.begin() + id);
    emit m_instance->questVecResized();
}

// I did only few examples because Qt may have some already implemented
// For example if timers including deltaTime is already in libraries, then it is not required to make these classes (like chrono etc.)
