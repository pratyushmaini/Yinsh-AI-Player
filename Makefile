 all: board.cpp player.cpp main.cpp minimax.cpp
	  g++ -o play main.cpp player.cpp board.cpp minimax.cpp -std=c++11
