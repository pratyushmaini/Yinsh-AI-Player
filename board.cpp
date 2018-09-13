#include<bits/stdc++.h> 
using namespace std; 



class Board{
	//position to what is contained in it -- pos = tuple of x, y where min y starts at bottom most node
	//"E" / "R"/ "RO" /"M"/"MO"/"I

	vector <vector<string>> mapping;
	vector<Cart> RingPos ;
	vector<Cart> RingPosOpp ;
	int min_rows[10]={1,0,0,0,0,1,1,2,3,4,6};
	int max_rows[10]={4,6,7,8,9,9,10,10,10,10,9};
	Cart last_selected;
	int ringsMy;
	int ringsOpp;

	Board(){
		for (i=0; i< 10; i++){
			vector<string> v;
			int max_rows_i = max_rows[i];
			int min_rows_i = min_rows[i];
			for (j=0; j<11; j++){
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
	void reverse(string s){
		//Board Psoitions "E" / "R" -- ring/ "RO" -- ring opp/"M"-- marker/"MO"/"I
		if (s.compare("E") == 0){
			return "E";
		}
		else if (s.compare("M") == 0){
			return "MO";
		}
		else if (s.compare("MO") == 0){
			return "M";
		}
		else{
			cerr << "THROW EXCEPTION3"<<endl;
		}
	}

	void flip(Cart start, Cart end){
		int x1 = start.x;
		int y1 = start.y;
		int x2 = end.x;
		int y2 = end.y;
		int delta_x = (x1-x2) ;
		int delta_y = (y1-y2) ;
		if (delta_x == 0 && delta_y > 0 ){
			for (i = y2 + 1; i<y1; i++){
				this.mapping[x1][i] = reverse(this.mapping[x1][i]);
			}
		}
		else if (delta_x == 0 && delta_y < 0){
			for (i = y1 + 1; i<y2; i++){
				this.mapping[x1][i] = reverse(this.mapping[x1][i]);
			}
		}
		else if (delta_y == 0 && delta_x > 0 ){
			for (i = x2 + 1; i<x1; i++){
				this.mapping[i][y1] = reverse(this.mapping[i][y1]);
			}
		}
		else if (delta_y == 0 && delta_x < 0 ){
			for (i = x1 + 1; i<x2; i++){
				this.mapping[i][y1] = reverse(this.mapping[i][y1]);
			}
		}
		else if (delta_y > 0  && delta_x > 0 ){
			for (i = 1; i<delta_x; i++){
				this.mapping[x2 + i][y2 + i] = reverse(this.mapping[x2 + i][y2 + i]);
			}
		}
		else if (delta_y < 0  && delta_x< 0 ){
			for (i = 1; i< -1*delta_x; i++){
				this.mapping[x1 + i][y1 + i] = reverse(this.mapping[x1 + i][y1 + i]);
			}
		}
		else{
			cerr << "THROW EXCEPTION" << endl;
		}

	}
	void removeMarkers(Cart start, Cart end){
		int x1 = start.x;
		int y1 = start.y;
		int x2 = end.x;
		int y2 = end.y;
		int delta_x = (x1-x2) ;
		int delta_y = (y1-y2) ;
		if (delta_x == 0 && delta_y == 4){
			for (i = y2; i<=y1; i++){
				this.mapping[x1][i] = "E";
			}
		}
		else if (delta_x == 0 && delta_y == -4){
			for (i = y1; i<=y2; i++){
				this.mapping[x1][i] = "E";
			}
		}
		else if (delta_y == 0 && delta_x == 4){
			for (i = x2; i<=x1; i++){
				this.mapping[i][y1] = "E";
			}
		}
		else if (delta_y == 0 && delta_x == -4){
			for (i = x1; i<=x2; i++){
				this.mapping[i][y1] = "E";
			}
		}
		else if (delta_y == 4 && delta_x == 4){
			for (i = 0; i<=4; i++){
				this.mapping[x2 + i][y2 + i] = "E";
			}
		}
		else if (delta_y == -4 && delta_x == -4){
			for (i = 0; i<=4; i++){
				this.mapping[x1 + i][y1 + i] = "E";
			}
		}
		else{
			cerr << "THROW EXCEPTION2" << endl;
		}
	}

	void execute_move(Cart tup, string type){
		//player = 0 means self
		//Assumes move is valid before being called
		//Types -- P, S, RE, RS, X, M
		//Board Psoitions "E" / "R" -- ring/ "RO" -- ring opp/"M"-- marker/"MO"/"I
		int x = tup.x;
		int y = tup.y;
		if (type == "P"){
			this.mapping[x][y] = "R";
			this.RingPos.push_back(tup);
		}
		else if (type == "S"){
			last_selected = tup;
			this.mapping[x][y] = "M";
			RingPos.erase(std::remove(RingPos.begin(), RingPos.end(), tup), RingPos.end());
		}
		else if (type == "M"){
			this.flip(this.last_selected, tup);
			this.RingPos.push_back(tup);
			this.last_selected = Cart temp();
		}
		else if (type == "X"){
			this.ringsMy --;
			this.RingPos.erase(std::remove(RingPos.begin(), RingPos.end(), tup), RingPos.end());
		}
		else if (type == "RS"){
			this.last_selected = tup;
		}
		else if (type == "RE"){
			this.removeMarkers(this.last_selected, tup);
			this.last_selected = Cart temp();
		}
	}

	void execute_move(Hex tup_hex, string type){
		Cart tup = convertToCart(tup_hex.ring, tup_hex.pos );
		return execute_move_opp(tup, type)
	}

	Hex convertToHex(int x, int y){
		int r = y;
		int p = 0;

		//Write Code here to convert
		Hex output(r,p);
		return output;

	}

	Cart convertToCart(int r, int p){
		int x = 0;
		int y = r;

		//Write Code here to convert
		Cart output(x,y);
		return output;

	}

	//final output -- M r p -- where M = move type, r = Ring no., p = position in ring starting from 0 


}

class Hex{
	public:
	int ring;
	int pos;
	
	Hex(int r, int p){
		ring = r;
		pos = p;
	}
}

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
}