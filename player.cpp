#include<bits/stdc++.h> 
using namespace std; 
#include "player.h"

void Player::play_move_seq(){

}

bool Player::placeRing(Cart tup){
	if (board.mapping[tup.x][tup.y] == "E" && state == 1){
		return true;
	}
	return false;
}

bool Player::selectRing(Cart tup){
	
}

bool Player::moveRing(Cart tup){

}
bool Player::removeRowStart(Cart tup){

}
bool Player::removeRowEnd(Cart tup){

}
bool Player::removeRing(Cart tup){

}

bool Player::IsValid(Cart tup, string type){
	if (type == "P"){
		return placeRing(tup);
	}
	else if (type == "S"){
		return selectRing(tup);
	}
	else if (type == "M"){
		return moveRing(tup);
	}
	else if (type == "X"){
		return removeRing(tup);
	}
	else if (type == "RS"){
		return removeRowStart(tup);
	}
	else if (type == "RE"){
		return removeRowEnd(tup);
	}
}

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
            cin>>s>>r>>p;
            cerr << s << endl;
            // std::string s = "split on    whitespace   ";
			// std::string s = "split on    whitespace   ";
			// std::vector<std::string> result;
			// std::istringstream iss(s);
			// for(std::string s; iss >> s; )
			//     result.push_back(s);
			Hex tup(stoi(r),stoi(p));
			// Cart tup = 
            board.execute_move(tup, s);
            // cout<<s<<endl;
            // cin>>move; 
            board.printConfig();
        }
    }
	
}



