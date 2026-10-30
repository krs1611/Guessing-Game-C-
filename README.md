# GuessMaster Suite (C++17)

An interactive, multi-mode terminal guessing game suite written in modern, standard **C++17**.

---

## 🎮 Game Modes

### 1. Classic Number Guessing
- **Difficulty Presets**:
  - **Easy**: 1 to 50 with 10 attempts
  - **Medium**: 1 to 100 with 7 attempts
  - **Hard**: 1 to 500 with 8 attempts
  - **Custom Range**: Custom bounds and attempts
- **Feedback & Hints**:
  - Directional guidance: `TOO HIGH ↑` or `TOO LOW ↓`
  - Proximity meter: *Freezing Cold*, *Cold*, *Lukewarm*, *Warm*, or *Burning Hot!!*
  - Dynamic bracket visualizer: tracks your current search interval `[ min < ? < max ]`
  - Guess history log

### 2. Word Mystery Guessing (Hangman)
- **Themed Categories**:
  - Programming & Tech
  - Animals & Nature
  - World Geography
  - Astronomy & Space
- **Features**:
  - Detailed 7-stage ASCII hangman gallows
  - Masked letter progress display
  - Used letters tracking
  - Hint system: Buy a letter hint by entering `?` (costs 1 life)
  - Full word guessing supported

### 3. Bulls & Cows (Mastermind Codebreaker)
- Guess a 4-digit secret code where every digit is unique.
- **Bulls (🎯)**: Correct digit in the exact position.
- **Cows (🐮)**: Correct digit in the wrong position.
- Formatted tabular history table tracking every round's deduction.

### 4. Player Statistics & Persistence
- Automatically records games played, victories, win rate %, current win streak, best win streak, and fewest attempts.
- Persists data to `scores.txt` across gaming sessions.
- In-game stat viewer and reset option.

---

## 📁 Project Structure

```
guessing_game_cpp/
├── CMakeLists.txt        # CMake build configuration
├── Makefile              # Standard Makefile (make, make run, make clean)
├── build.sh              # One-step compilation bash script
├── README.md             # Project documentation and guide
├── scores.txt            # Persistent player statistics (auto-generated)
├── include/              # Header files (.hpp)
│   ├── BullsAndCowsGame.hpp
│   ├── GameEngine.hpp
│   ├── NumberGuessGame.hpp
│   ├── ScoreManager.hpp
│   ├── Utils.hpp
│   └── WordGuessGame.hpp
└── src/                  # Implementation files (.cpp)
    ├── BullsAndCowsGame.cpp
    ├── GameEngine.cpp
    ├── NumberGuessGame.cpp
    ├── ScoreManager.cpp
    ├── Utils.cpp
    ├── WordGuessGame.cpp
    └── main.cpp
```

---

## 🛠️ Build and Compilation Instructions

### Prerequisites
- A modern C++ compiler supporting **C++17** (`g++`, `clang++`, or MSVC)
- `make` or `cmake`

### Method 1: Using the Makefile (Recommended)
```bash
# Compile the project
make

# Run the game
make run

# Clean build artifacts
make clean
```

### Method 2: Direct Compiler Invocation
```bash
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src/*.cpp -o guessing_game
./guessing_game
```

### Method 3: Using CMake
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./guessing_game
```

### Method 4: Using the Shell Script
```bash
chmod +x build.sh
./build.sh
./guessing_game
```

---

## 🎨 Terminal Visuals & Compatibility
- Uses standard ANSI escape codes for colors, bold weights, and clean headers.
- Works across Linux, macOS, and Windows 10/11 terminals (Windows Terminal / PowerShell).
- Safe input handling protects against EOF and invalid non-numeric inputs.
