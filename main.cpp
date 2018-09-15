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

    // if(player_id == 2) {
    //     // Get other player's move
    //     cin>>move; 
        
    //     while(true) {
    //         cout<<"P 1 0"<<endl;
    //         cin>>move;
    //         cerr << move << endl;
    //         usleep(microseconds);


    //     }
    // }   
    // else if(player_id == 1) {
    //     while(true) {
    //         cout<<"P 0 0"<<endl;
    //         cin>>move; 
    //         cerr << move << endl;
    //         usleep(microseconds);
    //     }
    // }
    return 0;
}
