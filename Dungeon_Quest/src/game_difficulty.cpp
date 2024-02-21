#include "game_difficulty.h"

GameDifficulty *GameDifficulty::m_instance = nullptr;
GameDifficulty::Difficulty GameDifficulty::m_difficulty = GameDifficulty::Difficulty::D_EASY;

GameDifficulty::GameDifficulty()
{
}

GameDifficulty::~GameDifficulty()
{
}

void GameDifficulty::setDifficulty(const int difficulty)
{
    m_difficulty = Difficulty(difficulty);
    // TODO: emit?
}

void GameDifficulty::instantiate()
{
    if (!m_instance)
    {
        m_instance = new GameDifficulty();
    }
}

void GameDifficulty::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

GameDifficulty *GameDifficulty::getInstance()
{
    return m_instance;
}
