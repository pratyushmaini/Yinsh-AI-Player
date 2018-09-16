#include <vector>
using namespace std;
#include<bits/stdc++.h> 
#include "board.h"


class Tup3 
{
public:
    // int num;
    vector<string> moves; 
    vector<Cart> carts;
    Tup3(vector<string> m, vector<Cart> c)
    {
        // num=n;
        moves=m;
        carts=c;
    }
    Tup3(){

    }
};

MoveVal DecisionMaker(Board board, int ply, int state);
MoveVal* MaxVal(Board board, float alpha, float beta, int ply, int state, MoveVal* prev_move);
MoveVal* MinVal(Board board, float alpha, float beta, int ply, int state, MoveVal* prev_move);

