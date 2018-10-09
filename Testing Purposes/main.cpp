#include "player.h"


unsigned int microseconds = 2000;


using namespace std;

int main(int argc, char** argv) {
    
    int player_id, board_size, time_limit;
    string a;
    string move;
    getline(cin, a);
    vector<string> results;
    boost::split(results, a, [](char c){return c == ' ';});
    Player myBot(stoi(results[0]), stoi(results[1]), stoi(results[2]));
    myBot.play();
    return 0;
}