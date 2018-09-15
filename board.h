#include <string>
#include <iostream>
#include <fstream>
#include <vector>
// #include "game.h"
using namespace std;
#include<bits/stdc++.h> 
using namespace std; 

class Hex{
	public:
	int ring;
	int pos;
	
	Hex(int r, int p){
		ring = r;
		pos = p;
	}
	bool operator==(Hex lhs, Hex rhs){
    return lhs.ring() == rhs.ring() && lhs.pos() == rhs.pos();
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
	bool operator==(Cart lhs, Cart rhs){
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
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
	std::vector<Board> children;
	string last_move; 
	
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
	void execute_move(Cart tup, string type);
	void execute_move_opp(Cart tup, string type);
	void execute_move(Hex tup_hex, string type);
	Hex convertToHex(int x, int y);
	Cart convertToCart(int r, int p);
	void printConfig();
	void execute_move_sequence(vector<Hex> tup_hexvec, vector<string> type_vec);
	void execute_move_sequence(vector<Cart> tup_hexvec, vector<string> type_vec);
	void addMarkers(Cart start, Cart end, bool self);
	void undo_move(Cart tup, string type);
	void undo_move_opp(Cart tup, string type);
	void undo_move(Hex tup_hex, string type);
	void printConfig();
	void undo_move_sequence(vector<Hex> tup_hexvec, vector<string> type_vec);
	void undo_move_sequence(vector<Cart> tup_hexvec, vector<string> type_vec);

};

