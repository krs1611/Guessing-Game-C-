#include "BullsAndCowsGame.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>

BullsAndCowsGame::BullsAndCowsGame(ScoreManager& scoreMgr)
    : m_scoreMgr(scoreMgr) {}

std::string BullsAndCowsGame::generateSecretCode(int length) {
    std::vector<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    // Shuffle
    for (int i = digits.size() - 1; i > 0; --i) {
        int j = Utils::getRandomInt(0, i);
        std::swap(digits[i], digits[j]);
    }
    // Prevent leading zero if preferred, but in Mastermind any 4 unique digits is fine
    std::string code;
    for (int i = 0; i < length; ++i) {
        code += digits[i];
    }
    return code;
}

bool BullsAndCowsGame::isValidGuess(const std::string& guess, int length, std::string& errorMsg) {
    if ((int)guess.length() != length) {
        errorMsg = "Guess must be exactly " + std::to_string(length) + " digits.";
        return false;
    }
    std::set<char> seen;
    for (char c : guess) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            errorMsg = "All characters must be numeric digits (0-9).";
            return false;
        }
        if (seen.count(c)) {
            errorMsg = "All digits must be unique (no duplicates).";
            return false;
        }
        seen.insert(c);
    }
    return true;
}

void BullsAndCowsGame::evaluateGuess(const std::string& secret, const std::string& guess, int& bulls, int& cows) {
    bulls = 0;
    cows = 0;
    for (size_t i = 0; i < guess.length(); ++i) {
        if (guess[i] == secret[i]) {
            bulls++;
        } else if (secret.find(guess[i]) != std::string::npos) {
            cows++;
        }
    }
}

void BullsAndCowsGame::displayHistory(const std::vector<RoundRecord>& history) {
    if (history.empty()) return;

    std::cout << "  " << Utils::Color::CYAN << "┌─────────┬──────────────┬──────────┬──────────┐" << Utils::Color::RESET << "\n";
    std::cout << "  " << Utils::Color::CYAN << "│ " << Utils::Color::BOLD << Utils::Color::WHITE << "Round   │ Guess Code   │ Bulls 🎯 │ Cows  🐮 " << Utils::Color::CYAN << "│" << Utils::Color::RESET << "\n";
    std::cout << "  " << Utils::Color::CYAN << "├─────────┼──────────────┼──────────┼──────────┤" << Utils::Color::RESET << "\n";

    for (const auto& r : history) {
        std::cout << "  " << Utils::Color::CYAN << "│  " << Utils::Color::WHITE << std::setw(6) << std::left << r.round 
                  << Utils::Color::CYAN << " │  " << Utils::Color::YELLOW << std::setw(11) << std::left << r.guess 
                  << Utils::Color::CYAN << " │  " << Utils::Color::GREEN << std::setw(7) << std::left << r.bulls 
                  << Utils::Color::CYAN << " │  " << Utils::Color::MAGENTA << std::setw(7) << std::left << r.cows 
                  << Utils::Color::CYAN << " │" << Utils::Color::RESET << "\n";
    }
    std::cout << "  " << Utils::Color::CYAN << "└─────────┴──────────────┴──────────┴──────────┘" << Utils::Color::RESET << "\n\n";
}

void BullsAndCowsGame::play() {
    Utils::clearScreen();
    Utils::printBanner();
    Utils::printHeader("BULLS & COWS (MASTERMIND)");

    std::cout << "  " << Utils::Color::CYAN << "RULES:" << Utils::Color::RESET << "\n";
    std::cout << "  • I have chosen a 4-digit secret code with unique digits.\n";
    std::cout << "  • " << Utils::Color::GREEN << "BULL (🎯):" << Utils::Color::RESET << " Correct digit in the exact right position.\n";
    std::cout << "  • " << Utils::Color::MAGENTA << "COW  (🐮):" << Utils::Color::RESET << " Correct digit, but in the wrong position.\n";
    std::cout << "  • You have 10 rounds to discover the full code (4 Bulls)!\n\n";

    std::string secret = generateSecretCode(4);
    int maxRounds = 10;
    int currentRound = 1;
    bool won = false;
    std::vector<RoundRecord> history;

    while (currentRound <= maxRounds) {
        std::cout << "  ─────────────────────────────────────────────────────────────\n";
        std::cout << "  Round " << Utils::Color::BOLD << currentRound << "/" << maxRounds 
                  << Utils::Color::RESET << " (" << Utils::Color::YELLOW << (maxRounds - currentRound + 1) 
                  << " attempts left" << Utils::Color::RESET << ")\n";

        displayHistory(history);

        std::string guess;
        while (true) {
            guess = Utils::getString("  Enter 4 unique digits (e.g., 5281): ");
            std::string errMsg;
            if (isValidGuess(guess, 4, errMsg)) {
                break;
            }
            std::cout << Utils::Color::RED << "  [!] " << errMsg << Utils::Color::RESET << "\n";
        }

        int bulls = 0, cows = 0;
        evaluateGuess(secret, guess, bulls, cows);
        history.push_back({currentRound, guess, bulls, cows});

        if (bulls == 4) {
            won = true;
            break;
        }

        std::cout << "  ➜ Result: " << Utils::Color::GREEN << Utils::Color::BOLD << bulls << " Bull(s) 🎯" 
                  << Utils::Color::RESET << " and " << Utils::Color::MAGENTA << Utils::Color::BOLD << cows 
                  << " Cow(s) 🐮" << Utils::Color::RESET << "\n\n";

        currentRound++;
    }

    Utils::clearScreen();
    Utils::printBanner();
    Utils::printHeader("BULLS & COWS - RESULTS");
    displayHistory(history);

    std::cout << "  ═════════════════════════════════════════════════════════════\n";
    if (won) {
        std::cout << Utils::Color::GREEN << Utils::Color::BOLD;
        std::cout << "  ★ CODE BREAKER! ★ You cracked the vault in " << currentRound 
                  << " round" << (currentRound == 1 ? "" : "s") << "!\n";
        std::cout << "  The secret code was: " << secret << "!" << Utils::Color::RESET << "\n";
    } else {
        std::cout << Utils::Color::RED << Utils::Color::BOLD;
        std::cout << "  ☠ SYSTEM LOCKED! You ran out of rounds.\n";
        std::cout << "  The secret code was: " << secret << "." << Utils::Color::RESET << "\n";
    }
    std::cout << "  ═════════════════════════════════════════════════════════════\n";

    m_scoreMgr.recordGame("bulls", won, currentRound);
    Utils::pressEnterToContinue();
}
