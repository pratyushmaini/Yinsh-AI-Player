 all: board.cpp player.cpp main.cpp 
	  g++ -o play main.cpp player.cpp board.cpp  -std=c++11
