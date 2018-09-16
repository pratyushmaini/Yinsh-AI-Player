#include <iostream>
#include <unistd.h>
#include "player.h"
#include <vector>
using namespace std;
#include<bits/stdc++.h> 

unsigned int microseconds = 2000;


using namespace std;

// Sample C++ Code 
int main(int argc, char** argv) {
    
    int player_id, board_size, time_limit;
    string move;
    // Get input from server about game specifications
    cin >> player_id >> board_size >> time_limit;
    Player myBot(player_id, board_size, time_limit);
    myBot.play();
    return 0;
}
