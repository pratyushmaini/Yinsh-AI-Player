#include <vector>
using namespace std;
#include<bits/stdc++.h> 
#include "board.h"

class MoveVal{
public:
  vector<string> movetype;
  vector<Cart> cart_xy;
  float utility;

  MoveVal(){

  }
  MoveVal(vector<string> m, vector<Cart> c, float u){
      movetype = m;
      cart_xy = c;
      utility = u;
  }
  MoveVal(float u){
      utility = u;
  }
};

class Children{
  public:
  vector<MoveVal> neighbours;
  int next_state;

  Children(vector<MoveVal> v, int state){
    neighbours = v;
    next_state = state;
  }
};

MoveVal DecisionMaker(Board board, int ply, int state);
MoveVal MaxVal(Board board, float alpha, float beta, int ply, int state, MoveVal prev_move);
MoveVal MinVal(Board board, float alpha, float beta, int ply, int state, MoveVal prev_move);