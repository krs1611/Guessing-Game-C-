CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRCS = src/main.cpp \
       src/GameEngine.cpp \
       src/NumberGuessGame.cpp \
       src/WordGuessGame.cpp \
       src/BullsAndCowsGame.cpp \
       src/ScoreManager.cpp \
       src/Utils.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = guessing_game

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) scores.txt
