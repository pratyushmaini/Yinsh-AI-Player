
#include "board.h"

class Player{
public:
	int player ; //0 or 1
	float time_left; 
	int board_size ;
	Board board;
	int seq_length;
	int rings_max;
	

	Player(int player_id, int board_size, float time_limit, int seq_length){
		board_size = board_size;
		rings_max = board_size;
		seq_length = seq_length;
		player 	= player_id;
		time_left 	= time_limit;
		cerr << "Beginning Board initiation" <<endl;
		Board board_temp(board_size, rings_max, seq_length);
		board = board_temp;
		// board = &board1;
		cerr << "Board Initialised" <<endl;
	}
	void play();
	void play_2(int ply, int countmv);

};