#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <bits/stdc++.h> 


class Hex{
	public:
	int ring;
	int pos;
	
	Hex(int r, int p){
		ring = r;
		pos = p;
	}
	bool operator==(Hex other){
    return ring == other.ring && pos == other.pos;
    }
};

class Cart{
	public:
	int x;
	int y;
	Cart (){

	}
	Cart (int a,int b){
		x = a;
		y = b;
	}
	bool operator==(Cart other){
    return x == other.x && y == other.y;
    }
};

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
  Children(){

  }
};
class Board{
	//position to what is contained in it -- pos = tuple of x, y where min y starts at bottom most node
	//"E" / "R"/ "RO" /"M"/"MO"/"I
public:
	vector <vector <string> > mapping;
	vector<Cart> RingPos ;
	vector<Cart> RingPosOpp ;
	int min_rows[11]={1,0,0,0,0,1,1,2,3,4,6};
	int max_rows[11]={4,6,7,8,9,9,10,10,10,10,9};
	Cart last_selected;
	int ringsMy;
	int ringsOpp;
	string last_move;
	int my_state = 1;
	int opp_state = 1;
	float utility_board;
	Children children;

	
	Board(){
		for (int i=0; i< 11; i++){
			vector<string> v;
			// int max_rows_i = max_rows[i];
			// int min_rows_i = min_rows[i];
			for (int j=0; j<11; j++){
				if (i<= max_rows[j] && i>= min_rows[j]){
					v.push_back("E");
				}
				else{
					v.push_back("I");
				}
			}
			mapping.push_back(v);
		}
		ringsMy = 5;
		ringsOpp = 5;		
	}
	string reverse(string s);
	void flip(Cart start, Cart end);
	void removeMarkers(Cart start, Cart end);


	void execute_move_my(Cart tup, string type);
	void execute_move_opp(Cart tup, string type);
	void execute_move_my(Hex tup_hex, string type);
	void execute_move_opp(Hex tup_hex, string type);
	
	void execute_move_sequence(vector<Cart> tup_vec, vector<string> type_vec, bool my_turn);
	void execute_move_sequence_my(vector<Hex> tup_hexvec, vector<string> type_vec);
	void execute_move_sequence_my(vector<Cart> tup_vec, vector<string> type_vec);
	void execute_move_sequence_opp(vector<Hex> tup_hexvec, vector<string> type_vec);
	void execute_move_sequence_opp(vector<Cart> tup_vec, vector<string> type_vec);

	void addMarkers(Cart start, Cart end, bool self);

	void undo_move_my(Cart tup, string type);
	void undo_move_opp(Cart tup, string type);
	void undo_move_my(Hex tup_hex, string type);
	void undo_move_opp(Hex tup_hex, string type);

	void undo_move_sequence(vector<Cart> tup_vec, vector<string> type_vec, bool my_turn);
	void undo_move_sequence_my(vector<Hex> tup_hexvec, vector<string> type_vec);
	void undo_move_sequence_my(vector<Cart> tup_vec, vector<string> type_vec);
	void undo_move_sequence_opp(vector<Hex> tup_hexvec, vector<string> type_vec);
	void undo_move_sequence_opp(vector<Cart> tup_vec, vector<string> type_vec);

	Hex convertToHex(int x, int y);
	Cart convertToCart(int r, int p);
	void printConfig();


	void find_children(int playerstate, bool my_turn);
	vector<MoveVal> placeRing(bool my_turn);
	vector<MoveVal> moveRing( bool my_turn);
	vector<MoveVal> find_neighbours(Cart c, int dir, bool my_turn);
	float find_utility(vector<Cart> ct, vector<string> m, float prev_utility);

};



