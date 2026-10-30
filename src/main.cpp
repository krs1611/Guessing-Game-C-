#include "GameEngine.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        GameEngine engine;
        engine.run();
    } catch (const std::exception& ex) {
        std::cerr << "\n[FATAL ERROR]: " << ex.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\n[FATAL ERROR]: An unknown error occurred.\n";
        return 1;
    }
    return 0;
}
