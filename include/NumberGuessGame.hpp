#ifndef NUMBER_GUESS_GAME_HPP
#define NUMBER_GUESS_GAME_HPP

#include "ScoreManager.hpp"
#include <vector>

class NumberGuessGame {
public:
    NumberGuessGame(ScoreManager& scoreMgr);
    void play();

private:
    ScoreManager& m_scoreMgr;

    void selectDifficulty(int& minVal, int& maxVal, int& maxAttempts, std::string& diffName);
    std::string getProximityHint(int guess, int target, int minVal, int maxVal);
    void displayRangeBracket(int lowBound, int highBound, int currentGuess, int target);
};

#endif // NUMBER_GUESS_GAME_HPP
