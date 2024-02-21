#ifndef GAME_DIFFICULTY_H
#define GAME_DIFFICULTY_H
#include <QObject>
// INFO: Making class because there is a problem with QML directly accessing enums
// Singleton
class GameDifficulty : public QObject
{
    Q_OBJECT
private:
    GameDifficulty();
    ~GameDifficulty();
public:
    enum class Difficulty
    {
        D_EASY = 0x0,
        D_MEDIUM = 0x1,
        D_HARD = 0x2,
        D_INSANE = 0x3
    };
    Q_ENUM(Difficulty)

    Q_INVOKABLE static void setDifficulty(const int difficulty); // Because QML
    inline static Difficulty getDifficulty()
    { return m_difficulty; }
    inline void operator=(const Difficulty difficulty)
    { m_difficulty = difficulty; }
    static void instantiate();
    static void destroy();
    static GameDifficulty *getInstance();
private:
    static GameDifficulty *m_instance;
    static Difficulty m_difficulty;
};
#endif // GAME_DIFFICULTY_H
