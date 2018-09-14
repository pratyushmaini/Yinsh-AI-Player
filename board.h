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

	Board(){
		for (int i=0; i< 10; i++){
			vector<string> v;
			int max_rows_i = max_rows[i];
			int min_rows_i = min_rows[i];
			for (int j=0; j<11; j++){
				if (j<= max_rows_i && j>= min_rows_i){
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
};

