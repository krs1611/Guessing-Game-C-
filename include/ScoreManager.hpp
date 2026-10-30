#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

#include <string>

struct GameStats {
    int gamesPlayed = 0;
    int gamesWon = 0;
    int bestScore = 999999; // Fewest attempts
    int currentStreak = 0;
    int bestStreak = 0;
};

class ScoreManager {
public:
    ScoreManager(const std::string& filename = "scores.txt");
    
    void recordGame(const std::string& mode, bool won, int attempts);
    void displayStats() const;
    void resetStats();

    void loadScores();
    void saveScores() const;

private:
    std::string m_filename;
    GameStats m_numberStats;
    GameStats m_wordStats;
    GameStats m_bullsStats;

    void updateStat(GameStats& stats, bool won, int attempts);
    void printStatCard(const std::string& title, const GameStats& stats) const;
};

#endif // SCORE_MANAGER_HPP
