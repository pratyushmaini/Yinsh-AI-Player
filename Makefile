 all: main.cpp player.cpp board.cpp minimax.cpp neighbours.cpp
	  g++ -o  play main.cpp player.cpp board.cpp minimax.cpp neighbours.cpp -std=c++11
