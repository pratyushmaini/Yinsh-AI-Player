#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class game
{
public:
	game();
	game::check_move_validity();
	check_player_state();
	get_current_player();
	calculate_score();
	get_score();
	execute_move();
};
