#ifndef __GAME_STATE__
#define __GAME_STATE__

// All possible game states (to be done)
#include <QObject>
// INFO: Making class because there is a problem with QML directly accessing enums
// Singleton
class GameState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ getState NOTIFY gameStateChanged)
private:
    GameState();
    ~GameState();
public:
    enum class State
    {
        GS_FIRST = 0x0,

        GS_FIRST_INIT = 0x01,
        GS_LOAD_SCENE = 0x02,
        GS_RUN_SCENE = 0x03, // main game logic (character in scene control)
        GS_LOAD_CUTSCENE = 0x04,
        GS_RUN_CUTSCENE = 0x05,

        GS_MAIN_MENU = 0x11,
        GS_PAUSE_MENU = 0x12,
        GS_LOAD_MENU = 0x13,
        GS_SAVE_MENU = 0x14,
        GS_SETTINGS_MENU = 0x15,
        GS_CREDITS_MENU = 0x16,

        GS_INVENTORY = 0x21,
        GS_TEXTBOX_POPUP = 0x22,
        GS_QUEST_POPUP = 0x23,
        GS_QUEST_LIST = 0x24,

        GS_GAME_OVER = 0x27,
        GS_PLAYER_DEAD = 0x28, // DEBUG

        GS_RESET = 0x30,

        GS_LAST = 0xFF
    };
    Q_ENUM(State)

    Q_INVOKABLE static void setState(const State state); // Because QML
    Q_INVOKABLE inline static State getState()
    { return m_state; }
    inline void operator=(const State state)
    { m_state = state; }
    static void instantiate();
    static void destroy();
    static GameState *getInstance();
private:
    static GameState *m_instance;
    static State m_state;
signals:
    void gameStateChanged();
};

#endif
