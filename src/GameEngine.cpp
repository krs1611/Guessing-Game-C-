#include "GameEngine.hpp"
#include "Utils.hpp"
#include <iostream>

GameEngine::GameEngine()
    : m_scoreMgr("scores.txt"),
      m_numberGame(m_scoreMgr),
      m_wordGame(m_scoreMgr),
      m_bullsGame(m_scoreMgr) {}

void GameEngine::displayMainMenu() {
    Utils::clearScreen();
    Utils::printBanner();

    std::cout << "  " << Utils::Color::CYAN << "MAIN MENU" << Utils::Color::RESET << "\n";
    std::cout << "  ─────────────────────────────────────────────────────────────\n";
    std::cout << "  " << Utils::Color::GREEN  << "[1] Classic Number Guessing" << Utils::Color::RESET 
              << "   (Custom range, hot/cold hints, bracket tracking)\n";
    std::cout << "  " << Utils::Color::YELLOW << "[2] Word Mystery Guessing" << Utils::Color::RESET 
              << "     (Hangman style with categories & letter hints)\n";
    std::cout << "  " << Utils::Color::MAGENTA<< "[3] Bulls & Cows (Mastermind)" << Utils::Color::RESET 
              << " (Deduction codebreaker game)\n";
    std::cout << "  " << Utils::Color::BLUE   << "[4] View Player Statistics" << Utils::Color::RESET 
              << "    (Win rates, streaks, best scores)\n";
    std::cout << "  " << Utils::Color::WHITE  << "[5] How to Play & Game Rules" << Utils::Color::RESET << "\n";
    std::cout << "  " << Utils::Color::RED    << "[6] Reset All Statistics" << Utils::Color::RESET << "\n";
    std::cout << "  " << Utils::Color::DIM    << "[7] Exit" << Utils::Color::RESET << "\n";
    std::cout << "  ─────────────────────────────────────────────────────────────\n\n";
}

void GameEngine::displayInstructions() {
    Utils::clearScreen();
    Utils::printBanner();
    Utils::printHeader("HOW TO PLAY & GAME RULES");

    std::cout << Utils::Color::BOLD << Utils::Color::GREEN << "1. Classic Number Guessing:" << Utils::Color::RESET << "\n";
    std::cout << "   • The computer selects a secret number within a chosen range (e.g. 1-100).\n";
    std::cout << "   • On every guess, you will be told if your guess was TOO HIGH or TOO LOW.\n";
    std::cout << "   • Proximity indicators inform you if you are Freezing, Cold, Warm, or Burning Hot!\n";
    std::cout << "   • The visual search bracket dynamically narrows as you eliminate ranges.\n\n";

    std::cout << Utils::Color::BOLD << Utils::Color::YELLOW << "2. Word Mystery Guessing (Hangman):" << Utils::Color::RESET << "\n";
    std::cout << "   • Pick a category (Programming, Animals, Geography, Astronomy).\n";
    std::cout << "   • Guess one letter at a time to reveal the mystery word.\n";
    std::cout << "   • You have 6 mistakes before the hangman gallows is completed.\n";
    std::cout << "   • Type '?' to buy a letter hint (costs 1 life) or guess the full word directly.\n\n";

    std::cout << Utils::Color::BOLD << Utils::Color::MAGENTA << "3. Bulls & Cows (Mastermind):" << Utils::Color::RESET << "\n";
    std::cout << "   • Guess a secret 4-digit code made of distinct digits (0-9).\n";
    std::cout << "   • Bulls (🎯): Correct digit in the exact position.\n";
    std::cout << "   • Cows  (🐮): Correct digit in the wrong position.\n";
    std::cout << "   • Use logic and deduction across 10 rounds to reach 4 Bulls!\n\n";

    Utils::pressEnterToContinue();
}

void GameEngine::run() {
    bool running = true;
    while (running) {
        displayMainMenu();
        int choice = Utils::getInt("  Enter your selection (1-7): ", 1, 7);

        switch (choice) {
            case 1:
                m_numberGame.play();
                break;
            case 2:
                m_wordGame.play();
                break;
            case 3:
                m_bullsGame.play();
                break;
            case 4:
                m_scoreMgr.displayStats();
                break;
            case 5:
                displayInstructions();
                break;
            case 6: {
                char confirm = Utils::getChar("  Are you sure you want to reset all stats? (Y/N): ", "YN");
                if (confirm == 'Y') {
                    m_scoreMgr.resetStats();
                }
                break;
            }
            case 7:
                running = false;
                Utils::clearScreen();
                std::cout << "\n" << Utils::Color::CYAN << Utils::Color::BOLD;
                std::cout << "  Thanks for playing GuessMaster Suite! Have a fantastic day!\n" << Utils::Color::RESET << "\n";
                break;
        }
    }
}
