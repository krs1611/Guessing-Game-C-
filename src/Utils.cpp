#include "Utils.hpp"
#include <algorithm>
#include <cctype>
#include <limits>
#include <random>
#include <sstream>

namespace Utils {

    void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
#else
        std::cout << "\033[2J\033[1;1H";
#endif
    }

    void printBanner() {
        std::cout << Color::CYAN << Color::BOLD;
        std::cout << R"(
  ╔══════════════════════════════════════════════════════════════╗
  ║      ██████╗ ██╗   ██╗███████╗███████╗███████╗██████╗        ║
  ║     ██╔════╝ ██║   ██║██╔════╝██╔════╝██╔════╝██╔══██╗       ║
  ║     ██║  ███╗██║   ██║█████╗  ███████╗███████╗██████╔╝       ║
  ║     ██║   ██║██║   ██║██╔══╝  ╚════██║╚════██║██╔══██╗       ║
  ║     ╚██████╔╝╚██████╔╝███████╗███████║███████║██║  ██║       ║
  ║      ╚═════╝  ╚═════╝ ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝       ║
  ║             ★  M A S T E R   S U I T E  ★                    ║
  ╚══════════════════════════════════════════════════════════════╝
)" << Color::RESET << "\n";
    }

    void printHeader(const std::string& title) {
        std::cout << "\n" << Color::MAGENTA << Color::BOLD;
        std::cout << "  ═══ [ " << title << " ] ═══" << Color::RESET << "\n\n";
    }

    void pressEnterToContinue() {
        std::cout << "\n" << Color::DIM << "Press Enter to return to menu..." << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    int getInt(const std::string& prompt, int minVal, int maxVal) {
        while (true) {
            std::cout << Color::YELLOW << prompt << Color::RESET;
            std::string line;
            if (!std::getline(std::cin, line)) {
                // Handle EOF
                std::cin.clear();
                return minVal;
            }
            line = trim(line);
            if (line.empty()) {
                std::cout << Color::RED << "  [!] Input cannot be empty. Please enter a number." << Color::RESET << "\n";
                continue;
            }
            std::stringstream ss(line);
            int value;
            if (ss >> value && ss.eof()) {
                if (value >= minVal && value <= maxVal) {
                    return value;
                }
                std::cout << Color::RED << "  [!] Out of range! Please enter a number between " 
                          << minVal << " and " << maxVal << "." << Color::RESET << "\n";
            } else {
                std::cout << Color::RED << "  [!] Invalid input! Please enter a valid whole number." << Color::RESET << "\n";
            }
        }
    }

    char getChar(const std::string& prompt, const std::string& allowedChars) {
        while (true) {
            std::cout << Color::YELLOW << prompt << Color::RESET;
            std::string line;
            if (!std::getline(std::cin, line)) {
                std::cin.clear();
                return allowedChars.empty() ? ' ' : allowedChars[0];
            }
            line = trim(line);
            if (line.empty()) {
                std::cout << Color::RED << "  [!] Input cannot be empty." << Color::RESET << "\n";
                continue;
            }
            char ch = static_cast<char>(std::toupper(line[0]));
            if (allowedChars.empty()) {
                return ch;
            }
            std::string upperAllowed = toUpper(allowedChars);
            if (upperAllowed.find(ch) != std::string::npos) {
                return ch;
            }
            std::cout << Color::RED << "  [!] Invalid choice! Expected one of: " << upperAllowed << Color::RESET << "\n";
        }
    }

    std::string getString(const std::string& prompt, bool allowEmpty) {
        while (true) {
            std::cout << Color::YELLOW << prompt << Color::RESET;
            std::string line;
            if (!std::getline(std::cin, line)) {
                std::cin.clear();
                return "";
            }
            line = trim(line);
            if (!allowEmpty && line.empty()) {
                std::cout << Color::RED << "  [!] Input cannot be empty." << Color::RESET << "\n";
                continue;
            }
            return line;
        }
    }

    std::string toUpper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return result;
    }

    std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
    }

    void printBox(const std::vector<std::string>& lines, const std::string& borderColor) {
        size_t maxLen = 0;
        for (const auto& l : lines) {
            if (l.length() > maxLen) maxLen = l.length();
        }
        maxLen = std::max(maxLen, size_t(30));

        std::cout << borderColor << "  ┌─" << std::string(maxLen + 2, '-') << "─┐" << Color::RESET << "\n";
        for (const auto& l : lines) {
            std::cout << borderColor << "  │  " << Color::RESET << l 
                      << std::string(maxLen - l.length(), ' ') 
                      << borderColor << "  │" << Color::RESET << "\n";
        }
        std::cout << borderColor << "  └─" << std::string(maxLen + 2, '-') << "─┘" << Color::RESET << "\n";
    }

    int getRandomInt(int minVal, int maxVal) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(minVal, maxVal);
        return dist(gen);
    }
}
