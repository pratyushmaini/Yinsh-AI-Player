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
			mapping[x1][i] = reverse(mapping[x1][i]);
		}
	}
	else if (delta_x == 0 && delta_y < 0){
		for (int i = y1 + 1; i<y2; i++){
			mapping[x1][i] = reverse(mapping[x1][i]);
		}
	}
	else if (delta_y == 0 && delta_x > 0 ){
		for (int i = x2 + 1; i<x1; i++){
			mapping[i][y1] = reverse(mapping[i][y1]);
		}
	}
	else if (delta_y == 0 && delta_x < 0 ){
		for (int i = x1 + 1; i<x2; i++){
			mapping[i][y1] = reverse(mapping[i][y1]);
		}
	}
	else if (delta_y > 0  && delta_x > 0 ){
		for (int i = 1; i<delta_x; i++){
			mapping[x2 + i][y2 + i] = reverse(mapping[x2 + i][y2 + i]);
		}
	}
	else if (delta_y < 0  && delta_x< 0 ){
		for (int i = 1; i< -1*delta_x; i++){
			mapping[x1 + i][y1 + i] = reverse(mapping[x1 + i][y1 + i]);
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
			mapping[x1][i] = "E";
		}
	}
	else if (delta_x == 0 && delta_y == -4){
		for (int i = y1; i<=y2; i++){
			mapping[x1][i] = "E";
		}
	}
	else if (delta_y == 0 && delta_x == 4){
		for (int i = x2; i<=x1; i++){
			mapping[i][y1] = "E";
		}
	}
	else if (delta_y == 0 && delta_x == -4){
		for (int i = x1; i<=x2; i++){
			mapping[i][y1] = "E";
		}
	}
	else if (delta_y == 4 && delta_x == 4){
		for (int i = 0; i<=4; i++){
			mapping[x2 + i][y2 + i] = "E";
		}
	}
	else if (delta_y == -4 && delta_x == -4){
		for (int i = 0; i<=4; i++){
			mapping[x1 + i][y1 + i] = "E";
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
		mapping[x][y] = "R";
		RingPos.push_back(tup);
	}
	else if (type == "S"){
		last_selected = tup;
		mapping[x][y] = "M";
		// RingPos.erase(std::remove(RingPos.begin(), RingPos.end(), tup), RingPos.end());
	}
	else if (type == "M"){
		flip(last_selected, tup);
		RingPos.push_back(tup);
		Cart last_selected();
		// last_selected = temp();
	}
	else if (type == "X"){
		ringsMy --;
		// RingPos.erase(std::remove(RingPos.begin(), RingPos.end(), tup), RingPos.end());
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
		mapping[x][y] = "RO";
		RingPosOpp.push_back(tup);
	}
	else if (type == "S"){
		last_selected = tup;
		mapping[x][y] = "MO";
		// RingPosOpp.erase(std::remove(RingPosOpp.begin(), RingPosOpp.end(), tup), RingPosOpp.end());
	}
	else if (type == "M"){
		flip(last_selected, tup);
		RingPosOpp.push_back(tup);
		Cart last_selected();
		// last_selected = temp();
	}
	else if (type == "X"){
		ringsOpp --;
		// RingPosOpp.erase(std::remove(RingPosOpp.begin(), RingPosOpp.end(), tup), RingPosOpp.end());
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

Hex Board::convertToHex(int x, int y){
	int r = y;
	int p = 0;

	//Write Code here to convert
	Hex output(r,p);
	return output;

}

Cart Board::convertToCart(int r, int p){
	int x = 0;
	int y = r;

	//Write Code here to convert
	Cart output(x,y);
	return output;

}


void Board::printConfig(){
	for (int i=0; i<mapping.size(); i++){
		for (int j = mapping[i].size() - 1; j >=0; j--){
			cout << mapping[i][j]<<", ";
		}
		cout << " "<<endl;
	}
}