#ifndef BULLS_AND_COWS_GAME_HPP
#define BULLS_AND_COWS_GAME_HPP

#include "ScoreManager.hpp"
#include <string>
#include <vector>

struct RoundRecord {
    int round;
    std::string guess;
    int bulls;
    int cows;
};

class BullsAndCowsGame {
public:
    BullsAndCowsGame(ScoreManager& scoreMgr);
    void play();

private:
    ScoreManager& m_scoreMgr;

    std::string generateSecretCode(int length = 4);
    bool isValidGuess(const std::string& guess, int length, std::string& errorMsg);
    void evaluateGuess(const std::string& secret, const std::string& guess, int& bulls, int& cows);
    void displayHistory(const std::vector<RoundRecord>& history);
};

#endif // BULLS_AND_COWS_GAME_HPP
