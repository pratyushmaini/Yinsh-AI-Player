
class MoveVal{
  vector<string> movetype;
  vector<Cart> cart_xy;
  vector<float> utility;

  MoveVal(){

  }
  MoveVal(vector<string> m, vector<Cart> c, vector<float> u){
      movetype = m;
      cart_xy = c;
      utility = u;
  }
}

MoveVal DecisionMaker(Board board, int ply);