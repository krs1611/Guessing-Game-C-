#include "NumberGuessGame.hpp"
#include "Utils.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

NumberGuessGame::NumberGuessGame(ScoreManager& scoreMgr)
    : m_scoreMgr(scoreMgr) {}

void NumberGuessGame::selectDifficulty(int& minVal, int& maxVal, int& maxAttempts, std::string& diffName) {
    Utils::clearScreen();
    Utils::printBanner();
    Utils::printHeader("NUMBER GUESS - SELECT DIFFICULTY");

    std::cout << "  " << Utils::Color::GREEN  << "[1] Easy   " << Utils::Color::RESET << "Range 1 to 50   | 10 Attempts\n";
    std::cout << "  " << Utils::Color::YELLOW << "[2] Medium " << Utils::Color::RESET << "Range 1 to 100  | 7 Attempts\n";
    std::cout << "  " << Utils::Color::RED    << "[3] Hard   " << Utils::Color::RESET << "Range 1 to 500  | 8 Attempts\n";
    std::cout << "  " << Utils::Color::CYAN   << "[4] Custom " << Utils::Color::RESET << "Customize Range & Attempts\n\n";

    int choice = Utils::getInt("  Select option (1-4): ", 1, 4);
    switch (choice) {
        case 1:
            minVal = 1; maxVal = 50; maxAttempts = 10; diffName = "Easy (1-50)";
            break;
        case 2:
            minVal = 1; maxVal = 100; maxAttempts = 7; diffName = "Medium (1-100)";
            break;
        case 3:
            minVal = 1; maxVal = 500; maxAttempts = 8; diffName = "Hard (1-500)";
            break;
        case 4:
            minVal = Utils::getInt("  Enter minimum number: ", 1, 10000);
            maxVal = Utils::getInt("  Enter maximum number: ", minVal + 5, minVal + 50000);
            maxAttempts = Utils::getInt("  Enter maximum attempts (1-30): ", 1, 30);
            diffName = "Custom (" + std::to_string(minVal) + "-" + std::to_string(maxVal) + ")";
            break;
    }
}

std::string NumberGuessGame::getProximityHint(int guess, int target, int minVal, int maxVal) {
    int diff = std::abs(guess - target);
    double pct = (double)diff / (maxVal - minVal);

    if (diff == 0) return Utils::Color::GREEN + "PERFECT MATCH!" + Utils::Color::RESET;
    if (pct <= 0.03 || diff <= 2) return Utils::Color::RED + Utils::Color::BOLD + "BURNING HOT!! Extremely Close!" + Utils::Color::RESET;
    if (pct <= 0.08 || diff <= 5) return Utils::Color::YELLOW + Utils::Color::BOLD + "WARM! Getting Close!" + Utils::Color::RESET;
    if (pct <= 0.18) return Utils::Color::CYAN + "LUKWARM (Moderate Distance)" + Utils::Color::RESET;
    if (pct <= 0.35) return Utils::Color::BLUE + "COLD (Far Away)" + Utils::Color::RESET;
    return Utils::Color::MAGENTA + "FREEZING COLD! (Way Off)" + Utils::Color::RESET;
}

void NumberGuessGame::displayRangeBracket(int lowBound, int highBound, int currentGuess, int target) {
    (void)currentGuess;
    (void)target;
    std::cout << "  " << Utils::Color::DIM << "Current Search Interval: " 
              << Utils::Color::BOLD << Utils::Color::WHITE 
              << "[ " << lowBound << " < ? < " << highBound << " ]" 
              << Utils::Color::RESET << "\n";
}

void NumberGuessGame::play() {
    int minVal = 1, maxVal = 100, maxAttempts = 7;
    std::string diffName = "Medium";
    selectDifficulty(minVal, maxVal, maxAttempts, diffName);

    int target = Utils::getRandomInt(minVal, maxVal);
    int attemptsUsed = 0;
    int lowBound = minVal;
    int highBound = maxVal;
    bool won = false;
    std::vector<int> guessHistory;

    Utils::clearScreen();
    Utils::printBanner();
    Utils::printHeader("NUMBER GUESS: " + diffName);
    std::cout << "  I have chosen a secret number between " 
              << Utils::Color::YELLOW << minVal << Utils::Color::RESET << " and " 
              << Utils::Color::YELLOW << maxVal << Utils::Color::RESET << ".\n";
    std::cout << "  You have " << Utils::Color::CYAN << maxAttempts 
              << Utils::Color::RESET << " attempts. Good luck!\n\n";

    while (attemptsUsed < maxAttempts) {
        int remaining = maxAttempts - attemptsUsed;
        std::cout << "  ─────────────────────────────────────────────────────────────\n";
        std::cout << "  Attempt " << Utils::Color::BOLD << (attemptsUsed + 1) << "/" << maxAttempts 
                  << Utils::Color::RESET << " (" << Utils::Color::YELLOW << remaining << " remaining" << Utils::Color::RESET << ")\n";
        displayRangeBracket(lowBound, highBound, 0, target);

        if (!guessHistory.empty()) {
            std::cout << "  " << Utils::Color::DIM << "Prior Guesses: ";
            for (size_t i = 0; i < guessHistory.size(); ++i) {
                std::cout << guessHistory[i] << (i + 1 < guessHistory.size() ? ", " : "");
            }
            std::cout << Utils::Color::RESET << "\n";
        }

        int guess = Utils::getInt("  Enter your guess: ", minVal, maxVal);
        attemptsUsed++;
        guessHistory.push_back(guess);

        if (guess == target) {
            won = true;
            break;
        }

        std::string direction = (guess < target) ? "TOO LOW ↑" : "TOO HIGH ↓";
        std::string dirColor = (guess < target) ? Utils::Color::CYAN : Utils::Color::MAGENTA;
        std::string proximity = getProximityHint(guess, target, minVal, maxVal);

        std::cout << "  ➜ " << dirColor << Utils::Color::BOLD << direction << Utils::Color::RESET 
                  << " | " << proximity << "\n\n";

        if (guess < target && guess > lowBound) lowBound = guess;
        if (guess > target && guess < highBound) highBound = guess;
    }

    std::cout << "\n  ═════════════════════════════════════════════════════════════\n";
    if (won) {
        std::cout << Utils::Color::GREEN << Utils::Color::BOLD;
        std::cout << "  ★ CONGRATULATIONS! ★ You cracked the code in " 
                  << attemptsUsed << " attempt" << (attemptsUsed == 1 ? "" : "s") << "!\n";
        std::cout << "  The secret number was indeed: " << target << "!" << Utils::Color::RESET << "\n";
    } else {
        std::cout << Utils::Color::RED << Utils::Color::BOLD;
        std::cout << "  ☠ GAME OVER! You ran out of attempts.\n";
        std::cout << "  The secret number was: " << target << "." << Utils::Color::RESET << "\n";
    }
    std::cout << "  ═════════════════════════════════════════════════════════════\n";

    m_scoreMgr.recordGame("number", won, attemptsUsed);
    Utils::pressEnterToContinue();
}
