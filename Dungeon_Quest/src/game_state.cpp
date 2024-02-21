#include "game_state.h"

GameState *GameState::m_instance = nullptr;
GameState::State GameState::m_state = GameState::State::GS_FIRST_INIT;

GameState::GameState()
{
}

GameState::~GameState()
{
}

void GameState::setState(const State state)
{
    m_state = state;
    emit m_instance->gameStateChanged();
}

void GameState::instantiate()
{
    if (!m_instance)
    {
        m_instance = new GameState();
    }
}

void GameState::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

GameState *GameState::getInstance()
{
    return m_instance;
}
