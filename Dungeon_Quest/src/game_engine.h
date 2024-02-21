#ifndef __GAME_ENGINE__
#define __GAME_ENGINE__

#include <QObject>
#include <QQuickItem>
#include <QVariant>
#include <QTimer>
#include <QKeyEvent>
#include <QQmlContext>
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>
#include <memory.h>
#include "camera.h"
#include "Time.h"
#include "keyboard.h"
#include "mouse.h"
#include "game_state.h"
#include "object.h"
#include "player.h"
#include "inventory.h"
#include "textbox.h"
#include "tilegenerator.h"
#include "base_scene.h"
#include "quest.h"
#include "entity_actions.h"
#include "event_logger.h"

// Must be part of QObjects because it is initialized by Qt
class GameEngine : public QObject
{
    Q_OBJECT
    // For getting window width
    Q_PROPERTY(int window_w READ getWindowWidth NOTIFY windowWidthSet)
    // For getting window height
    Q_PROPERTY(int window_h READ getWindowHeight NOTIFY windowHeightSet)
    // All the object that will be behaving as they need too
    Q_PROPERTY(QVariant objects READ getObjects NOTIFY objVecResized)
    Q_PROPERTY(QVariant quests READ getQuests NOTIFY questVecResized)
    Q_PROPERTY(int quest_count READ getQuestCount NOTIFY questVecResized)
    Q_PROPERTY(QVariant temp_quest READ getTempQuest NOTIFY tempQuestModified)
    Q_PROPERTY(QVariant active_quest READ getActiveQuest NOTIFY activeQuestModified)
    Q_PROPERTY(QVariant player READ getPlayer NOTIFY playerModified)
    Q_PROPERTY(int run_result READ runFrame NOTIFY frameFinished)
private:
    static const char *M_LOG_GAME_ENGINE;
    static Camera *m_maincam;
    static Time *m_time;
    static Keyboard *m_keyboard;
    static Mouse *m_mouse;
    static GameState *m_gamestate;
    static EventLogger *m_event_logger;
    static Player *m_player;
    static std::vector<Object*> *m_objects; // all the objects
    static QAudioOutput *m_aud_out_ambi;
    static QAudioOutput *m_aud_out_pl;
    static QMediaPlayer m_ambient_music;
    static QMediaPlayer m_player_debug;
    static std::vector<std::shared_ptr<BaseScene>> m_scenes;
    static size_t m_current_scene;
    static bool m_debug_key_subtr;
    static bool m_debug_key_add;
    static bool m_debug_key_ctrl;
    static bool m_debug_key_escape;
    static bool m_debug_button_l;
    static bool m_debug_button_r;
    static bool m_debug_button_m;
    static tileGenerator m_generator;
    //std::vector<Tile*> m_tiles;
    static std::vector<Tile*> *m_tiles;
    static std::vector<Quest*> m_quests;
    static Quest *m_temp_quest; // Waiting for Accept to be pushed back?
    static Quest *m_active_quest;
    static Inventory *m_inventory/*(5, 5)*/; // TODO: Make shared_ptr if setup never called from QML
    static TextBox *m_textbox;
    //static EntityQuest m_quest;
    static int m_window_width;
    static int m_window_height;
    static float m_previous_fixed_update; // TODO: Decide if it is necessary to put it here
    static QTimer *m_timer;
    //QKeyEvent *m_key_event;
    static bool m_setup_enabled;
    static bool m_reset_enabled;
    static bool m_init_success;
    static bool m_connected;
    static GameEngine *m_instance;

    GameEngine(int argc, char *argv[], QQmlContext *qml_context, QObject *parent = nullptr);
    ~GameEngine();
    static bool init(); // Inits everything what would be in constructor and returns if anything fails
public:
    static bool instantiate(int argc, char *argv[], QQmlContext *qml_context, QObject *parent = nullptr);
    static void destroy();
    static GameEngine *getInstance();
    static QVariant getObjects();// const;
    static QVariant getQuests();
    static QVariant getTempQuest();
    static QVariant getActiveQuest();
    static QVariant getPlayer();
    static int getQuestCount();
    Q_INVOKABLE static QVariant getObject(int index);// const;

    static int getWindowWidth();// const;  // Because Qt cannot access variables directly
    static int getWindowHeight();// const;  // Because Qt cannot access variables directly
    Q_INVOKABLE static void setup(); // set up all the necessary dependencies at startup
    Q_INVOKABLE static void reset(); // for resetting the game
    void setGameState(const GameState::State state); // TEST
    Q_INVOKABLE void switchCursor();
    static void newQuest(Quest *quest);
    Q_INVOKABLE static void claimQuest();
    Q_INVOKABLE static void declineQuest();
    Q_INVOKABLE static void completeQuest(int id);
    Q_INVOKABLE static void enableQuestPreview(int id);
    Q_INVOKABLE static void disableQuestPreview();
    Q_INVOKABLE static void disableQuestPreviews();
    Q_INVOKABLE static void setActiveQuest(int id);
    Q_INVOKABLE static void disableActiveQuest();
    Q_INVOKABLE static void setAllQuestsAsInactive();
    static void addObject(Object *obj);
private:
    static void debugSceneLoader();
    //static void objectSceneEraser();
    static void questEraser();
    static void loadScene(int id);
    static void camChangeDetector();
    static void gameState(); // Switch containig all the possible game states
    static void runScene(); // All the updates for in-game play
    static void update();  // Uptade for animations, input etc.
    static void fixedUpdate(); // Update for physics behavior
    static bool destroyProjectileOnDistanceReached(Object *obj, int &i);
    static void objectVsObjectInteractions();
    static void objectVsTileInteractions();
    static void physicalVsPhysical(Physical *phys_i, Physical *phys_j, int &i, int &j);
    static void physicalVsDoor(Physical *phys_i, Door *door_j, int &i, int &j);
    static void entityVsEntity(Entity *ent_i, Entity *ent_j, int &i, int &j);
    static void entityVsEntityAttack(Entity *ent_i, Entity *ent_j, int &i, int &j);
    static void entityVsProjectile(Entity *ent_i, Projectile *proj_j, int &i, int &j);
    static void entityVsItem(Entity *ent_i, Item *item_j, int &i, int &j);
    static void DEBUGResetTileCollisionVisibility();
    static void DEBUGShowTileVsMouseCollision(Tile *tile, Physical *phys);
    static void eventEnterPauseMenu();
    static void eventEnterInventory();
    static void eventOpenQuestList();
    static void eventMouseInteract();
    static void eventMouseClickOnObject(Object *obj);
    static void eventQuestActionOnObjectInteract(Object *object, EntityActions action);
    static bool moveObjectToScene(Object *obj, int scene_id, int obj_id); // scene_id is scene pos in vec of scenes and obj_id is obj pos in vec of objs
    static void runLoadScene();
    static void runLoadCutscene();
    static void runCutscene();
    static void runMainMenu();
    static void runPauseMenu();
    static void runInventory();
    static void runTextboxPopup();
    static void runQuestPopup();
    static void runQuestList();
signals:
    void windowWidthSet();  // Tell Qt that window width was set
    void windowHeightSet();  // Tell Qt that window height was set
    void frameFinished();
    void objVecResized();
    void questVecResized();
    void tempQuestModified();
    void activeQuestModified();
    void playerModified();
public slots:
    static int runFrame(); // Main function for running the game (no loop because Qt... every call of this function means update logic and inputs)
    //TODO: this needs to be refactored because otherwise Qt won't use it (find function which can run this without separate loop)
};

#endif


// TODO: If drawing is handled by Qt Quick (which it is), remove all draw functions from all classes in all files
// TODO: Make camera pos shifter in relation to player pos and camera borders
