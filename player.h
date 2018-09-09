#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "game.h"

using namespace std;

class player
{
public:
	player();
	place_ring();
	select_ring();
	move_ring();
	remove_row_start();
	remove_row_end();
	remove_ring();
	play_move_seq();
	play();
};