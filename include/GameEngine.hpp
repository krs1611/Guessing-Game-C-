#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "ScoreManager.hpp"
#include "NumberGuessGame.hpp"
#include "WordGuessGame.hpp"
#include "BullsAndCowsGame.hpp"

class GameEngine {
public:
    GameEngine();
    void run();

private:
    ScoreManager m_scoreMgr;
    NumberGuessGame m_numberGame;
    WordGuessGame m_wordGame;
    BullsAndCowsGame m_bullsGame;

    void displayMainMenu();
    void displayInstructions();
};

#endif // GAME_ENGINE_HPP
