#!/bin/bash

CXX=g++
CXXFLAGS="-Wall -Wextra -O2"
LIBS="-lncurses"
OUTPUT="game"

SOURCES="
	entity.cpp
	dynamic_entity.cpp
	brick.cpp
	coin.cpp
	enemy.cpp
	collision_handler.cpp
	input_manager.cpp
	key_code.hpp
	physics.cpp
	level.cpp
	mario.cpp
	render.cpp
	game.cpp
	main.cpp
	config.hpp
"

echo "Compiling..."
$CXX $CXXFLAGS $SOURCES $LIBS -o $OUTPUT

if [ $? -eq 0 ]; then
    echo "✅ Build successful! Run ./$OUTPUT"
else
    echo "❌ Build failed!"
    exit 1
fi
