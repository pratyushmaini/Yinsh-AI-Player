
#include "board.h"

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
		cerr << "Beginning Board initiation" <<endl;
		Board board();
		cerr << "Board Initialised" <<endl;
	}
	void play();

};