
#include "player.h"
 


void Player::play(){
	// board.printConfig();
	if(player == 2) {
    	while(true) {
            string a, s,r,p ; 
            getline(cin, a);
            cerr << a << endl;
			vector<string> results;
			boost::split(results, a, [](char c){return c == ' ';});
            vector<Hex> Hexvec;
            vector<string> strVec;
            vector<Cart> Cartvec;
            for (int q=0; q<results.size(); q+=3){
            	s = results[q];
            	r = results[q+1];
            	p = results[q+2];
            	Hex tup(stoi(r),stoi(p));
				Hexvec.push_back(tup);
				Cart my_cart = board.convertToCart(tup.ring, tup.pos);
            	Cartvec.push_back(my_cart);
				strVec.push_back(s);
            }
            board.prev_Opp_move = Tup3(strVec, Cartvec);
		
			board.execute_move_sequence_opp(Hexvec, strVec);

            // board.printConfig();

            int ply = 1;
            if (board.my_state == 1 && board.RingPos.size() == 5){
            	board.my_state = 2;
            	ply = 1;
            }
            // if (board.opp_state == 1 && board.RingPosOpp.size() == 5){
            // 	board.opp_state = 2;
            // 	ply = 1;
            // }
            MoveVal next_move = DecisionMaker(board, ply, board.my_state);//****************************
            board.execute_move_sequence_my(next_move.cart_xy, next_move.movetype);
            cerr << "Checking Decision " << endl;
            vector<Hex> my_hex_vec;
            for (int r = 0; r< next_move.cart_xy.size(); r++){
                Hex my_hex = board.convertToHex(next_move.cart_xy[r].x , next_move.cart_xy[r].y);	  
                my_hex_vec.push_back(my_hex);      	
                cout << next_move.movetype[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }
            cout << endl;	

            // board.printConfig();

            
        }
    }   
    else if(player == 1) {
        while(true) {
            string a, s,r,p ;
            int ply = 1;
            if (board.my_state == 1 && board.RingPos.size() == 5){
            	board.my_state = 2;
            	ply = 1;
            }
            // if (board.opp_state == 1 && board.RingPosOpp.size() == 5){
            // 	board.opp_state = 2;
            // 	ply = 1;
            // }
            MoveVal next_move = DecisionMaker(board, ply, board.my_state);//****************************
            board.execute_move_sequence_my(next_move.cart_xy, next_move.movetype);
            cerr << "Checking Decision " << endl;
            vector<Hex> my_hex_vec;
            for (int r = 0; r< next_move.cart_xy.size(); r++){
                Hex my_hex = board.convertToHex(next_move.cart_xy[r].x , next_move.cart_xy[r].y);	  
                my_hex_vec.push_back(my_hex);      	
                cout << next_move.movetype[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }
            cout << endl;	

            // board.printConfig();

            getline(cin, a);
            cerr << a << endl;
			vector<string> results;
			boost::split(results, a, [](char c){return c == ' ';});
            vector<Hex> Hexvec;
            vector<string> strVec;
            vector<Cart> Cartvec;
            for (int q=0; q<results.size(); q+=3){
            	s = results[q];
            	r = results[q+1];
            	p = results[q+2];
            	Hex tup(stoi(r),stoi(p));
            	Cart my_cart = board.convertToCart(tup.ring, tup.pos);
            	Cartvec.push_back(my_cart);
				Hexvec.push_back(tup);
				strVec.push_back(s);
            }
            board.prev_Opp_move = Tup3(strVec, Cartvec);
		
			board.execute_move_sequence_opp(Hexvec, strVec);

            // board.printConfig();
        }
    }
	
}



