#include<bits/stdc++.h> 
using namespace std; 
#include "player.h"


// void Player::play_move_seq(){
// }

// bool Player::placeRing(Cart tup){
// 	if (board.mapping[tup.x][tup.y] == "E" && board.my_state == 1){
// 		return true;
// 	}
// 	return false;
// }

// bool Player::selectRing(Cart tup){
// }

// bool Player::moveRing(Cart tup){
// }

// bool Player::removeRowStart(Cart tup){

// }
// bool Player::removeRowEnd(Cart tup){

// }
// bool Player::removeRing(Cart tup){

// }

// bool Player::IsValid(Cart tup, string type){
// 	if (type == "P"){
// 		return placeRing(tup);
// 	}
// 	else if (type == "S"){
// 		return selectRing(tup);
// 	}
// 	else if (type == "M"){
// 		return moveRing(tup);
// 	}
// 	else if (type == "X"){
// 		return removeRing(tup);
// 	}
// 	else if (type == "RS"){
// 		return removeRowStart(tup);
// 	}
// 	else if (type == "RE"){
// 		return removeRowEnd(tup);
// 	}
// }

void Player::play(){
	board.printConfig();
	if(player == 2) {
    // Get other player's move
        // string move;
        // cin>>move;         
        // while(true) {
        //     string a ;
        //     getline(cin,a);
        //     cerr << a << endl;
        //     cout<<a<<endl;
        //     cin>>move;
        //     board.printConfig();
        // }
    }   
    else if(player == 1) {
        while(true) {
        	cout <<"Play"<<endl;
            string s,r,p ;
            // getline(cin,s);
            if (board.my_state == 1 && board.RingPos.size() == 5){
            	board.my_state = 2;
            }
            if (board.opp_state == 1 && board.RingPosOpp.size() == 5){
            	board.opp_state = 2;
            }
            MoveVal next_move = DecisionMaker(board, 1, board.my_state);//****************************
            board.execute_move_sequence_my(next_move.cart_xy, next_move.movetype);
            
            cin>>s>>r>>p;
            cerr << s << endl;
			Hex tup(stoi(r),stoi(p));
			vector<Hex> Hexvec;
			Hexvec.push_back(tup);
			vector<string> strVec;
			strVec.push_back(s);
			board.execute_move_sequence_opp(Hexvec, strVec);
/////////////////////////////////OPPPOBNET MOVE WRITE BELOW///////////////////////////////*************************
			// board.execute_move_sequence(opp_move.movetype, opp_move.cart_xy);//Correct opponrnt's move
			// Cart tup = 
			
            // cout<<s<<endl;
            // cin>>move; 
            board.printConfig();
            cout << "OUTPUT PRINT HERE IN HEX FORM" <<endl; 
        }
    }
	
}



