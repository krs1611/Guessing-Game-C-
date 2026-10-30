#include "WordGuessGame.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iostream>
#include <set>

WordGuessGame::WordGuessGame(ScoreManager& scoreMgr)
    : m_scoreMgr(scoreMgr) {
    initWordBank();
}

void WordGuessGame::initWordBank() {
    m_wordBank["Programming & Tech"] = {
        "ALGORITHM", "COMPILER", "POINTER", "RECURSION", "VARIABLE", 
        "INHERITANCE", "DATABASE", "ASSEMBLY", "POLYMORPHISM", "TEMPLATE",
        "BYTECODE", "FRAMEWORK", "INTERFACE", "CONTAINER", "COROUTINE"
    };
    m_wordBank["Animals & Nature"] = {
        "ELEPHANT", "KANGAROO", "PENGUIN", "CHAMELEON", "CHEETAH",
        "PLATYPUS", "DOLPHIN", "FLAMINGO", "OCTOPUS", "RHINOCEROS",
        "ALLIGATOR", "HEDGEHOG", "GIRAFFE", "JELLYFISH", "WOODPECKER"
    };
    m_wordBank["World Geography"] = {
        "AUSTRALIA", "GERMANY", "BRAZIL", "PORTUGAL", "SINGAPORE",
        "SWITZERLAND", "ARGENTINA", "NORWAY", "ICELAND", "INDONESIA",
        "MADAGASCAR", "NETHERLANDS", "COLOMBIA", "THAILAND", "NEWZEALAND"
    };
    m_wordBank["Astronomy & Space"] = {
        "ASTEROID", "GALAXY", "NEBULA", "SUPERNOVA", "TELESCOPE",
        "CONSTELLATION", "BLACKHOLE", "SATELLITE", "PLANETARIUM", "EXOPLANET"
    };
}

void WordGuessGame::drawGallows(int mistakesLeft) const {
    const char* stages[7] = {
        R"(
         ┌────┐
         │    │
         │    O
         │   /|\
         │   / \
         │
      ───────┴──────)", // 0 mistakes left (game over)
        R"(
         ┌────┐
         │    │
         │    O
         │   /|\
         │   / 
         │
      ───────┴──────)", // 1 mistake left
        R"(
         ┌────┐
         │    │
         │    O
         │   /|\
         │   
         │
      ───────┴──────)", // 2 mistakes left
        R"(
         ┌────┐
         │    │
         │    O
         │   /|
         │   
         │
      ───────┴──────)", // 3 mistakes left
        R"(
         ┌────┐
         │    │
         │    O
         │    |
         │   
         │
      ───────┴──────)", // 4 mistakes left
        R"(
         ┌────┐
         │    │
         │    O
         │   
         │   
         │
      ───────┴──────)", // 5 mistakes left
        R"(
         ┌────┐
         │    │
         │   
         │   
         │   
         │
      ───────┴──────)"  // 6 mistakes left (clean)
    };

    int idx = std::clamp(mistakesLeft, 0, 6);
    std::string color = (idx <= 1) ? Utils::Color::RED : (idx <= 3 ? Utils::Color::YELLOW : Utils::Color::CYAN);
    std::cout << color << stages[idx] << Utils::Color::RESET << "\n\n";
}

void WordGuessGame::printMaskedWord(const std::string& secret, const std::vector<bool>& revealed) const {
    std::cout << "  Word:  " << Utils::Color::BOLD << Utils::Color::WHITE;
    for (size_t i = 0; i < secret.length(); ++i) {
        if (revealed[i]) {
            std::cout << secret[i] << " ";
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << Utils::Color::RESET << "  (" << secret.length() << " letters)\n\n";
}

void WordGuessGame::play() {
    Utils::clearScreen();
    Utils::printBanner();
    Utils::printHeader("WORD GUESS - SELECT CATEGORY");

    std::vector<std::string> categories = {
        "Programming & Tech",
        "Animals & Nature",
        "World Geography",
        "Astronomy & Space"
    };

    int catIdx = 1;
    for (const auto& cat : categories) {
        std::cout << "  [" << catIdx << "] " << Utils::Color::YELLOW << cat << Utils::Color::RESET << "\n";
        catIdx++;
    }
    std::cout << "  [" << catIdx << "] " << Utils::Color::CYAN << "Random Category" << Utils::Color::RESET << "\n\n";

    int catChoice = Utils::getInt("  Select category (1-" + std::to_string(catIdx) + "): ", 1, catIdx);
    std::string selectedCategory;
    if (catChoice == catIdx) {
        selectedCategory = categories[Utils::getRandomInt(0, categories.size() - 1)];
    } else {
        selectedCategory = categories[catChoice - 1];
    }

    const auto& wordList = m_wordBank[selectedCategory];
    std::string secret = wordList[Utils::getRandomInt(0, wordList.size() - 1)];
    std::vector<bool> revealed(secret.length(), false);
    std::set<char> guessedLetters;
    int lives = 6;
    int turns = 0;
    bool won = false;
    std::string statusMessage = "";

    while (lives > 0) {
        Utils::clearScreen();
        Utils::printBanner();
        Utils::printHeader("WORD GUESS: " + selectedCategory);

        drawGallows(lives);
        printMaskedWord(secret, revealed);

        std::cout << "  Lives remaining: " << Utils::Color::YELLOW << lives << "/6" << Utils::Color::RESET << "\n";
        std::cout << "  Guessed letters: " << Utils::Color::MAGENTA;
        if (guessedLetters.empty()) {
            std::cout << "(none)";
        } else {
            for (char c : guessedLetters) std::cout << c << " ";
        }
        std::cout << Utils::Color::RESET << "\n";
        std::cout << "  " << Utils::Color::DIM << "(Tip: Enter a single letter, full word, or '?' for a hint)" << Utils::Color::RESET << "\n\n";

        if (!statusMessage.empty()) {
            std::cout << statusMessage << "\n\n";
            statusMessage = "";
        }

        std::string input = Utils::toUpper(Utils::getString("  Your guess: "));
        if (input.empty()) continue;

        turns++;

        // Hint command
        if (input == "?") {
            if (lives <= 1) {
                statusMessage = Utils::Color::RED + "  [!] Cannot buy a hint with only 1 life left!" + Utils::Color::RESET;
                continue;
            }
            std::vector<size_t> unrevealedIndices;
            for (size_t i = 0; i < secret.length(); ++i) {
                if (!revealed[i]) unrevealedIndices.push_back(i);
            }
            if (!unrevealedIndices.empty()) {
                size_t randIdx = unrevealedIndices[Utils::getRandomInt(0, unrevealedIndices.size() - 1)];
                char hintChar = secret[randIdx];
                for (size_t i = 0; i < secret.length(); ++i) {
                    if (secret[i] == hintChar) revealed[i] = true;
                }
                guessedLetters.insert(hintChar);
                lives--;
                statusMessage = Utils::Color::YELLOW + "  [★] HINT: Revealed letter '" + std::string(1, hintChar) 
                                + "' (-1 life penalty!)" + Utils::Color::RESET;
            }
            if (std::all_of(revealed.begin(), revealed.end(), [](bool v) { return v; })) {
                won = true;
                break;
            }
            continue;
        }

        // Validate that input contains letters only
        bool allAlpha = std::all_of(input.begin(), input.end(), [](unsigned char c) {
            return std::isalpha(c);
        });
        if (!allAlpha) {
            statusMessage = Utils::Color::RED + "  [!] Please enter alphabetic characters only." + Utils::Color::RESET;
            continue;
        }

        // Full word guess
        if (input.length() > 1) {
            if (input == secret) {
                won = true;
                for (size_t i = 0; i < secret.length(); ++i) revealed[i] = true;
                break;
            } else {
                lives -= 2;
                statusMessage = Utils::Color::RED + "  [✗] Incorrect full word guess! (-2 lives!)" + Utils::Color::RESET;
                continue;
            }
        }

        // Single letter guess
        char guessChar = input[0];
        if (guessedLetters.count(guessChar)) {
            statusMessage = Utils::Color::YELLOW + "  [!] You already guessed '" + std::string(1, guessChar) + "'." + Utils::Color::RESET;
            continue;
        }

        guessedLetters.insert(guessChar);
        bool match = false;
        for (size_t i = 0; i < secret.length(); ++i) {
            if (secret[i] == guessChar) {
                revealed[i] = true;
                match = true;
            }
        }

        if (match) {
            statusMessage = Utils::Color::GREEN + "  [✓] Great guess! '" + std::string(1, guessChar) + "' is in the word." + Utils::Color::RESET;
        } else {
            lives--;
            statusMessage = Utils::Color::RED + "  [✗] Sorry, '" + std::string(1, guessChar) + "' is not in the word." + Utils::Color::RESET;
        }

        // Check if all letters revealed
        if (std::all_of(revealed.begin(), revealed.end(), [](bool v) { return v; })) {
            won = true;
            break;
        }
    }

    Utils::clearScreen();
    Utils::printBanner();
    drawGallows(lives);
    std::cout << "\n  ═════════════════════════════════════════════════════════════\n";
    if (won) {
        std::cout << Utils::Color::GREEN << Utils::Color::BOLD;
        std::cout << "  ★ VICTORY! ★ You successfully guessed the word!\n";
        std::cout << "  The mystery word was: " << secret << "!\n";
        std::cout << "  Finished with " << lives << " lives remaining in " << turns << " turns." << Utils::Color::RESET << "\n";
    } else {
        std::cout << Utils::Color::RED << Utils::Color::BOLD;
        std::cout << "  ☠ DEFEAT! The hangman was completed.\n";
        std::cout << "  The mystery word was: " << secret << ".\n";
    }
    std::cout << "  ═════════════════════════════════════════════════════════════\n";

    m_scoreMgr.recordGame("word", won, turns);
    Utils::pressEnterToContinue();
}
