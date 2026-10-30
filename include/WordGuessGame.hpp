#ifndef WORD_GUESS_GAME_HPP
#define WORD_GUESS_GAME_HPP

#include "ScoreManager.hpp"
#include <string>
#include <vector>
#include <map>

class WordGuessGame {
public:
    WordGuessGame(ScoreManager& scoreMgr);
    void play();

private:
    ScoreManager& m_scoreMgr;
    std::map<std::string, std::vector<std::string>> m_wordBank;

    void initWordBank();
    void drawGallows(int mistakesLeft) const;
    void printMaskedWord(const std::string& secret, const std::vector<bool>& revealed) const;
};

#endif // WORD_GUESS_GAME_HPP
