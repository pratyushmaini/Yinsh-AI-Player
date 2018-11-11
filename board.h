#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp>
#include <time.h>


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

  bool operator< (const MoveVal &other) const {
        return utility < other.utility;
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


class Board{
	//position to what is contained in it -- pos = tuple of x, y where min y starts at bottom most node
	//"E" / "R"/ "RO" /"M"/"MO"/"I
public:
	vector <vector <string> > mapping;
	vector<Cart> RingPos ;
	vector<Cart> RingPosOpp ;
	vector<int> min_rows_5{1,0,0,0,0,  1,1,2,3,4,6};
	vector<int> min_rows_6{1,0,0,0,0,0,1,1,2,3,4,5,7};
	vector<int> max_rows_5{4,6,7,8,    9,9, 10,10,10,10,  9};
	vector<int> max_rows_6{5,7,8,9,10,11,11,12,12,12,12,12,11};
	Cart last_selected;
	int ringsMy; //Number of rings on the side
	int ringsOpp;
	int markersMy; //Number of my markers on the board
	int markersOpp;
	string last_move;
	int my_state ;
	int opp_state = 1;
	Tup3 prev_Opp_move;
	int seq_length;
	int rings_max;
	int board_size;

	
	Board(int board_size_in, int rings_max_in, int seq_length_in){
		cerr << board_size_in << " " << rings_max_in << " "<< seq_length_in << " Params" << endl;
		board_size = board_size_in;
		rings_max = rings_max_in;
		seq_length = seq_length_in;
		vector<int> min_rows;
		vector<int>max_rows;
		if (board_size == 5){
			min_rows = min_rows_5;
			max_rows = max_rows_5;
		}
		else{
			min_rows = min_rows_6;
			max_rows = max_rows_6;
		}

		for (int i=0; i< board_size*2 + 1 ; i++){
			vector<string> v;
			// int max_rows_i = max_rows[i];
			// int min_rows_i = min_rows[i];
			for (int j=0; j<board_size*2 + 1; j++){
				if (i<= max_rows[j] && i>= min_rows[j]){
					v.push_back("E");
				}
				else{
					v.push_back("I");
				}
			}
			mapping.push_back(v);
		}
		ringsMy = 0;
		ringsOpp = 0;
		markersMy = 0;
		markersOpp = 0;	
		my_state = 1;	
	}
	Board(){

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


	Children find_children(int playerstate, bool my_turn);
	vector<MoveVal> placeRing(bool my_turn);
	vector<MoveVal> moveRing( bool my_turn);
	vector<MoveVal> find_neighbours(/*Cart opp_c_in, Cart opp_c_fin,*/ Cart c, int dir, bool my_turn);
	float find_utility();
	float find_utility_mini();
	float find_utility_master(bool type);
	float all_utility();
	float all_utility_opp();
	float edge_utility();
	float rings_utility();



	vector<Tup3> check_row_vertical(int init_pos_x,int init_pos_y,bool my_turn);
	vector<Tup3> check_row_horizontal(int init_pos_x,int init_pos_y,bool my_turn);
	vector<Tup3> check_row_diagonal(int init_pos_x,int init_pos_y,bool my_turn);
	vector<Tup3> check_row_all_points(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y ,bool my_turn);
	vector<Tup3> check_row(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y );
	vector<Tup3> check_row_all_points_each( int init_pos_x,int init_pos_y,int check,bool my_turn );
	int check_if_row(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y, int ring_x, int ring_y, bool my_turn);
	Tup3 CheckRowsMadeByOpp(Cart opp_c_in, Cart opp_c_fin, bool my_turn);

	vector<Tup3> check_row_vertical_my( int init_pos_x,int init_pos_y,bool my_turn );
	vector<Tup3> check_row_vertical_opp( int init_pos_x,int init_pos_y,bool my_turn );
	vector<Tup3> check_row_horizontal_my( int init_pos_x,int init_pos_y,bool my_turn );
	vector<Tup3> check_row_horizontal_opp( int init_pos_x,int init_pos_y ,bool my_turn);
	vector<Tup3> check_row_diagonal_my( int init_pos_x,int init_pos_y,bool my_turn);
	vector<Tup3> check_row_diagonal_opp( int init_pos_x,int init_pos_y,bool my_turn);



	float utility_check_row_vertical(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y );
    float utility_check_row_horizontal(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y );
    float utility_check_row_diagonal(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y );
    float utility_check_row_all_points(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y );
    float utility_check_row(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y );


    MoveVal DecisionMaker(int ply, int state, bool util_type);
	MoveVal MaxVal(float alpha, float beta, int ply, bool util_type);//, int nodes);
	MoveVal MinVal(float alpha, float beta, int ply, bool util_type);//, int nodes);
};





