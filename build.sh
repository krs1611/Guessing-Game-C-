#!/usr/bin/env bash
set -e

echo "=== Building GuessMaster C++ Game Suite ==="
make clean
make -j$(nproc 2>/dev/null || echo 2)

echo ""
echo "Build successful! Executable generated: ./guessing_game"
echo "To run the game, execute: ./guessing_game"
