#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include<bits/stdc++.h> 
#include "minimax.h"

class Player{
public:
	int player ; //0 or 1
	float time_left; 
	int board_size ;
	Board board;
	

	Player(int player_id, int board_size, float time_limit){
		board_size = board_size;
		player 	= player_id;
		time_left 	= time_limit;
		cout << "Beginning Board initiation" <<endl;
		Board board();
		
		cout << "Board Initialised" <<endl;
		// board 		= temp_board;
	}
	// void play_move_seq();
	void play();
	// bool placeRing(Cart tup);
	// bool selectRing(Cart tup);
	// bool moveRing(Cart tup);
	// bool removeRowStart(Cart tup);
	// bool removeRowEnd(Cart tup);
	// bool removeRing(Cart tup);
	// bool IsValid(Cart tup, string type);
};