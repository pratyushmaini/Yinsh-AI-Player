
#!/bin/bash

## Compile our two program files
g++ -std=c++11 -Ofast -march=native -o code main.cpp player.cpp board.cpp minimax.cpp neighbours.cpp
