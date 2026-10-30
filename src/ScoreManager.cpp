#include "ScoreManager.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

ScoreManager::ScoreManager(const std::string& filename)
    : m_filename(filename) {
    loadScores();
}

void ScoreManager::updateStat(GameStats& stats, bool won, int attempts) {
    stats.gamesPlayed++;
    if (won) {
        stats.gamesWon++;
        stats.currentStreak++;
        if (stats.currentStreak > stats.bestStreak) {
            stats.bestStreak = stats.currentStreak;
        }
        if (attempts > 0 && attempts < stats.bestScore) {
            stats.bestScore = attempts;
        }
    } else {
        stats.currentStreak = 0;
    }
    saveScores();
}

void ScoreManager::recordGame(const std::string& mode, bool won, int attempts) {
    if (mode == "number") {
        updateStat(m_numberStats, won, attempts);
    } else if (mode == "word") {
        updateStat(m_wordStats, won, attempts);
    } else if (mode == "bulls") {
        updateStat(m_bullsStats, won, attempts);
    }
}

void ScoreManager::printStatCard(const std::string& title, const GameStats& stats) const {
    double winRate = (stats.gamesPlayed > 0) ? (100.0 * stats.gamesWon / stats.gamesPlayed) : 0.0;
    std::string bestScoreStr = (stats.bestScore == 999999) ? "N/A" : std::to_string(stats.bestScore) + " tries";

    std::cout << Utils::Color::CYAN << "  ┌──────────────────────────────────────────────────┐" << Utils::Color::RESET << "\n";
    std::cout << Utils::Color::CYAN << "  │ " << Utils::Color::BOLD << Utils::Color::WHITE 
              << std::left << std::setw(48) << title << Utils::Color::CYAN << " │" << Utils::Color::RESET << "\n";
    std::cout << Utils::Color::CYAN << "  ├──────────────────────────────────────────────────┤" << Utils::Color::RESET << "\n";
    std::cout << Utils::Color::CYAN << "  │  Played: " << Utils::Color::YELLOW << std::setw(10) << stats.gamesPlayed 
              << Utils::Color::CYAN << " │  Won: " << Utils::Color::GREEN << std::setw(12) << stats.gamesWon 
              << Utils::Color::CYAN << " │" << Utils::Color::RESET << "\n";
    std::cout << Utils::Color::CYAN << "  │  Win Rate: " << Utils::Color::MAGENTA << std::fixed << std::setprecision(1) 
              << winRate << "%" << std::setw(6) << ""
              << Utils::Color::CYAN << " │  Best Score: " << Utils::Color::WHITE << std::setw(10) << bestScoreStr 
              << Utils::Color::CYAN << " │" << Utils::Color::RESET << "\n";
    std::cout << Utils::Color::CYAN << "  │  Streak: " << Utils::Color::YELLOW << std::setw(10) << stats.currentStreak 
              << Utils::Color::CYAN << " │  Best Streak: " << Utils::Color::GREEN << std::setw(7) << stats.bestStreak 
              << Utils::Color::CYAN << " │" << Utils::Color::RESET << "\n";
    std::cout << Utils::Color::CYAN << "  └──────────────────────────────────────────────────┘" << Utils::Color::RESET << "\n\n";
}

void ScoreManager::displayStats() const {
    Utils::printHeader("PLAYER STATISTICS & LEADERBOARD");
    printStatCard("Classic Number Guessing", m_numberStats);
    printStatCard("Word Mystery Guessing", m_wordStats);
    printStatCard("Bulls & Cows (Mastermind)", m_bullsStats);
    Utils::pressEnterToContinue();
}

void ScoreManager::resetStats() {
    m_numberStats = GameStats();
    m_wordStats = GameStats();
    m_bullsStats = GameStats();
    saveScores();
    std::cout << "\n" << Utils::Color::GREEN << "  [✓] All statistics have been reset successfully!" << Utils::Color::RESET << "\n";
    Utils::pressEnterToContinue();
}

void ScoreManager::loadScores() {
    std::ifstream in(m_filename);
    if (!in.is_open()) return;

    auto readStat = [&](GameStats& s) {
        in >> s.gamesPlayed >> s.gamesWon >> s.bestScore >> s.currentStreak >> s.bestStreak;
    };

    readStat(m_numberStats);
    readStat(m_wordStats);
    readStat(m_bullsStats);
}

void ScoreManager::saveScores() const {
    std::ofstream out(m_filename);
    if (!out.is_open()) return;

    auto writeStat = [&](const GameStats& s) {
        out << s.gamesPlayed << " " << s.gamesWon << " " << s.bestScore << " " 
            << s.currentStreak << " " << s.bestStreak << "\n";
    };

    writeStat(m_numberStats);
    writeStat(m_wordStats);
    writeStat(m_bullsStats);
}
