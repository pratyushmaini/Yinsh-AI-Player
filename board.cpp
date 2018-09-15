#include<bits/stdc++.h> 
using namespace std; 
#include "board.h"



//position to what is contained in it -- pos = tuple of x, y where min y starts at bottom most node
//"E" / "R"/ "RO" /"M"/"MO"/"I

string Board::reverse(string s){
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

void Board::flip(Cart start, Cart end){
	int x1 = start.x;
	int y1 = start.y;
	int x2 = end.x;
	int y2 = end.y;
	int delta_x = (x1-x2) ;
	int delta_y = (y1-y2) ;
	if (delta_x == 0 && delta_y > 0 ){
		for (int i = y2 + 1; i<y1; i++){
			mapping[i][x1] = reverse(mapping[i][x1]);
		}
	}
	else if (delta_x == 0 && delta_y < 0){
		for (int i = y1 + 1; i<y2; i++){
			mapping[i][x1] = reverse(mapping[i][x1]);
		}
	}
	else if (delta_y == 0 && delta_x > 0 ){
		for (int i = x2 + 1; i<x1; i++){
			mapping[y1][i] = reverse(mapping[y1][i]);
		}
	}
	else if (delta_y == 0 && delta_x < 0 ){
		for (int i = x1 + 1; i<x2; i++){
			mapping[y1][i] = reverse(mapping[y1][i]);
		}
	}
	else if (delta_y > 0  && delta_x > 0 ){
		for (int i = 1; i<delta_x; i++){
			mapping[y2 + i][x2+i] = reverse(mapping[y2 + i][x2+i]);
		}
	}
	else if (delta_y < 0  && delta_x< 0 ){
		for (int i = 1; i< -1*delta_x; i++){
			mapping[y1 + i][x1+i] = reverse(mapping[y1 + i][x1+i]);
		}
	}
	else{
		cerr << "THROW EXCEPTION" << endl;
	}

}
void Board::removeMarkers(Cart start, Cart end){
	int x1 = start.x;
	int y1 = start.y;
	int x2 = end.x;
	int y2 = end.y;
	int delta_x = (x1-x2) ;
	int delta_y = (y1-y2) ;
	if (delta_x == 0 && delta_y == 4){
		for (int i = y2; i<=y1; i++){
			mapping[i][x1] = "E";
		}
	}
	else if (delta_x == 0 && delta_y == -4){
		for (int i = y1; i<=y2; i++){
			mapping[i][x1] = "E";
		}
	}
	else if (delta_y == 0 && delta_x == 4){
		for (int i = x2; i<=x1; i++){
			mapping[y1][i] = "E";
		}
	}
	else if (delta_y == 0 && delta_x == -4){
		for (int i = x1; i<=x2; i++){
			mapping[y1][i] = "E";
		}
	}
	else if (delta_y == 4 && delta_x == 4){
		for (int i = 0; i<=4; i++){
			mapping[y2 + i][x2+i] = "E";
		}
	}
	else if (delta_y == -4 && delta_x == -4){
		for (int i = 0; i<=4; i++){
			mapping[y1 + i][x1+i] = "E";
		}
	}
	else{
		cerr << "THROW EXCEPTION2" << endl;
	}
}
void Board::addMarkers(Cart start, Cart end, bool self){
	string marker ;
	if (self){
		marker = "M";
	}
	else{
		marker = "MO";
	}
	int x1 = start.x;
	int y1 = start.y;
	int x2 = end.x;
	int y2 = end.y;
	int delta_x = (x1-x2) ;
	int delta_y = (y1-y2) ;
	if (delta_x == 0 && delta_y == 4){
		for (int i = y2; i<=y1; i++){
			mapping[i][x1] = marker;
		}
	}
	else if (delta_x == 0 && delta_y == -4){
		for (int i = y1; i<=y2; i++){
			mapping[i][x1] = marker;
		}
	}
	else if (delta_y == 0 && delta_x == 4){
		for (int i = x2; i<=x1; i++){
			mapping[y1][i] = marker;
		}
	}
	else if (delta_y == 0 && delta_x == -4){
		for (int i = x1; i<=x2; i++){
			mapping[y1][i] = marker;
		}
	}
	else if (delta_y == 4 && delta_x == 4){
		for (int i = 0; i<=4; i++){
			mapping[y2 + i][x2+i] = marker;
		}
	}
	else if (delta_y == -4 && delta_x == -4){
		for (int i = 0; i<=4; i++){
			mapping[y1 + i][x1+i] = marker;
		}
	}
	else{
		cerr << "THROW EXCEPTION2" << endl;
	}
}

void Board::execute_move(Cart tup, string type){
	//player = 0 means self
	//Assumes move is valid before being called
	//Types -- P, S, RE, RS, X, M
	//Board Psoitions "E" / "R" -- ring/ "RO" -- ring opp/"M"-- marker/"MO"/"I
	int x = tup.x;
	int y = tup.y;
	if (type == "P"){
		mapping[y][x] = "R";
		RingPos.push_back(tup);
	}
	else if (type == "S"){
		last_selected = tup;
		mapping[y][x] = "M";
		RingPos.erase(std::remove(RingPos.begin(), RingPos.end(), tup), RingPos.end());
	}
	else if (type == "M"){
		flip(last_selected, tup);
		RingPos.push_back(tup);
		Cart last_selected();
		// last_selected = temp();
	}
	else if (type == "X"){
		ringsMy --;
		RingPos.erase(std::remove(RingPos.begin(), RingPos.end(), tup), RingPos.end());
	}
	else if (type == "RS"){
		last_selected = tup;
	}
	else if (type == "RE"){
		removeMarkers(last_selected, tup);
		Cart last_selected();
		// last_selected = temp();
	}
}

void Board::execute_move_opp(Cart tup, string type){
	//player = 0 means self
	//Assumes move is valid before being called
	//Types -- P, S, RE, RS, X, M
	//Board Psoitions "E" / "R" -- ring/ "RO" -- ring opp/"M"-- marker/"MO"/"I
	int x = tup.x;
	int y = tup.y;
	if (type == "P"){
		mapping[y][x] = "RO";
		RingPosOpp.push_back(tup);
	}
	else if (type == "S"){
		last_selected = tup;
		mapping[y][x] = "MO";
		RingPosOpp.erase(std::remove(RingPosOpp.begin(), RingPosOpp.end(), tup), RingPosOpp.end());
	}
	else if (type == "M"){
		flip(last_selected, tup);
		RingPosOpp.push_back(tup);
		Cart last_selected();
		// last_selected = temp();
	}
	else if (type == "X"){
		ringsOpp --;
		RingPosOpp.erase(std::remove(RingPosOpp.begin(), RingPosOpp.end(), tup), RingPosOpp.end());
	}
	else if (type == "RS"){
		last_selected = tup;
	}
	else if (type == "RE"){
		removeMarkers(last_selected, tup);
		Cart last_selected();
		// last_selected = temp(); 
	}
}

void Board::execute_move(Hex tup_hex, string type){
	Cart tup = convertToCart(tup_hex.ring, tup_hex.pos );
	execute_move_opp(tup, type);
}

void Board::execute_move_sequence(vector<Hex> tup_hexvec, vector<string> type_vec){
	for (int i=0; i<tup_hexvec.size(); i++){
		execute_move(tup_hexvec[i],type_vec[i]);
	}
}

void Board::execute_move_sequence(vector<Cart> tup_cart, vector<string> type_vec){
	for (int i=0; i<tup_cart.size(); i++){
		execute_move(tup_cart[i],type_vec[i]);
	}
}

void Board::undo_move(Cart tup, string type){

}

void Board::undo_move_opp(Cart tup, string type){
	//player = 0 means self
	//Assumes move is valid before being called
	//Types -- P, S, RE, RS, X, M
	//Board Psoitions "E" / "R" -- ring/ "RO" -- ring opp/"M"-- marker/"MO"/"I
	int x = tup.x;
	int y = tup.y;
	if (type == "P"){
		mapping[y][x] = "E";
		RingPosOpp.pop_back();
	}
	else if (type == "S"){
		flip(last_selected, tup);
		mapping[y][x] = "RO";
		RingPosOpp.push_back(tup);
		Cart last_selected();
	}
	else if (type == "M"){
		
		last_selected = tup;
		mapping[y][x] = "E";
		RingPosOpp.erase(std::remove(RingPosOpp.begin(), RingPosOpp.end(), tup), RingPosOpp.end());
		
		// last_selected = temp();
	}
	else if (type == "X"){
		ringsOpp ++;
		RingPosOpp.push_back(tup);
	}
	else if (type == "RS"){
		addMarkers(last_selected, tup);
		Cart last_selected();
	}
	else if (type == "RE"){
		last_selected = tup;
		// last_selected = temp(); 
	}
}
void Board::undo_move(Hex tup_hex, string type){
	Cart tup = convertToCart(tup_hex.ring, tup_hex.pos );
	undo_move_opp(tup, type);
}

void Board::undo_move_sequence(vector<Hex> tup_hexvec, vector<string> type_vec){
	for (int i= tup_hexvec.size() - 1; i>=0; i--){
		undo_move(tup_hexvec[i],type_vec[i]);
	}
}
void Board::undo_move_sequence(vector<Cart> tup_cart, vector<string> type_vec){
	for (int i= tup_cart.size() - 1; i>=0; i--){
		undo_move(tup_cart[i],type_vec[i]);
	}
}

Hex solve_sec(int x, int y){
	int r,p;
	if (x>=0){
		
		if (y>=x){
			r = y;
			p = x;
		}
		else if (y>= 0 && y<x){
			r = x;
			p = 2*r - y ;
		}
		else if (y<0 && y<x){
			r = x - y;
			p = 3*r - x; 
	Board::	}

	}
	return Hex(r,p);
}

Hex Board::convertToHex(int x, int y){
	x = x-5;
	y = y-5;
	int p = 0;
	if (x>=0){
		Hex output = solve_sec(x,y);
		return output;
	}
//else
		x = -x;
		y = -y;
		Hex temp = solve_sec(x,y);
		Hex output(temp.ring, 3*temp.ring + temp.pos);
		return output;
	//15
}
Cart solve(int r, int p){
	int y = r;
	int x = 0;
	if (p<r){
		x = p;
	}
	else if (p<2*r){
		x = r;
		y = 2*r - p;
	}
	else if (p<3*r){
		x = 3*r - p;
		y = 2*r - p;
	}
	Cart output(x,y);
	return output;
}

Cart Board::convertToCart(int r, int p){
	int x,y;

	if (p>=3*r){
		int p_prime = p - 3*r;
		Cart temp = solve (r, p_prime);
		x = -temp.x;
		y = -temp.y;
	}
	else{
		Cart temp = solve (r, p);
		x = temp.x;
		y = temp.y;
	}

	x+=5; y+=5;
	//Write Code here to convert
	Cart output(x,y);
	return output;

}

void Board::printConfig(){
	for (int i = mapping.size() - 1; i >=0; i--){
		for (int j = 0; j < mapping[i].size() ; j++){
			cout << mapping[i][j]<<", ";
			Cart temp_cart(j,i);
			Cart temp2 = convertToCart(convertToHex(j,i).ring, convertToHex(j,i).pos);
			if (j==temp2.x && i == temp2.y){

			}
			else{
				cout <<"ERROR" << endl;
				cout << "x, y initial:" << j<< ", "<<i<<endl;
				cout << "x, y final:" << temp2.x<< ", "<<temp2.y<<endl;
			}
		}
		cout << " "<<endl;
	}
}