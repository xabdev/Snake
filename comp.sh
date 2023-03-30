#!/bin/bash

echo "compiling..."
g++ main.cpp items.cpp player.cpp maingame.cpp  -lncurses -o p && ./p

