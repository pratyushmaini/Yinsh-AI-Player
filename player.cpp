
#include "player.h"

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
            int ply = 1;
            if (board.my_state == 1 && board.RingPos.size() == 5){
            	board.my_state = 2;
            	ply = 1;
            }
            if (board.opp_state == 1 && board.RingPosOpp.size() == 5){
            	board.opp_state = 2;
            	ply = 1;
            }
            MoveVal next_move = DecisionMaker(board, ply, board.my_state);//****************************
            board.execute_move_sequence_my(next_move.cart_xy, next_move.movetype);
            cout << "Checking Decision " << endl;
            vector<Hex> my_hex_vec;
            for (int r = 0; r< next_move.cart_xy.size(); r++){
                Hex my_hex = board.convertToHex(next_move.cart_xy[r].x , next_move.cart_xy[r].y);	  
                my_hex_vec.push_back(my_hex);      	
                cout << next_move.movetype[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }
            cout << endl;	

            
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



