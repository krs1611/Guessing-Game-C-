#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <iostream>

namespace Utils {
    // ANSI Color and Style Codes
    namespace Color {
        const std::string RESET   = "\033[0m";
        const std::string BOLD    = "\033[1m";
        const std::string DIM     = "\033[2m";
        const std::string RED     = "\033[31m";
        const std::string GREEN   = "\033[32m";
        const std::string YELLOW  = "\033[33m";
        const std::string BLUE    = "\033[34m";
        const std::string MAGENTA = "\033[35m";
        const std::string CYAN    = "\033[36m";
        const std::string WHITE   = "\033[37m";
        const std::string BG_BLUE = "\033[44m";
        const std::string BG_DARK = "\033[40m";
    }

    void clearScreen();
    void printBanner();
    void printHeader(const std::string& title);
    void pressEnterToContinue();

    int getInt(const std::string& prompt, int minVal, int maxVal);
    char getChar(const std::string& prompt, const std::string& allowedChars = "");
    std::string getString(const std::string& prompt, bool allowEmpty = false);

    std::string toUpper(const std::string& str);
    std::string toLower(const std::string& str);
    std::string trim(const std::string& str);

    void printBox(const std::vector<std::string>& lines, const std::string& borderColor = Color::CYAN);
    int getRandomInt(int minVal, int maxVal);
}

#endif // UTILS_HPP
