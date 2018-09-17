
#include "player.h"
 


void Player::play(){
	// board.printConfig();
	// int ply = 2;
	if(player == 2) {
		int countermv = 0;
    	while(true) {
    		if (countermv <= 5) countermv ++;
    		if (countermv > 5) {
    			board.my_state = 2;
    		}
    		else {
    			board.my_state = 1;
    		}
    		// board.printConfig();
    		int ply = 2;
            string a, s,r,p ; 
            getline(cin, a);
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
            Cart opp_c_in, opp_c_fin;
            bool found = false;
			for (int r = 0; r< board.prev_Opp_move.moves.size(); r++){
				if (board.prev_Opp_move.moves[r] == "S"){
					opp_c_in = board.prev_Opp_move.carts[r];
					opp_c_fin = board.prev_Opp_move.carts[r+1];
					found = true;
					break;
				}
			}

			board.execute_move_sequence_opp(Hexvec, strVec);
			// cerr << "Opp move executed" << endl;
			Tup3 prefix;
			if (found){
			prefix = board.CheckRowsMadeByOpp(opp_c_in, opp_c_fin, true);
			}

            MoveVal next_move = DecisionMaker(board, ply, board.my_state);//****************************
            
            board.execute_move_sequence_my(next_move.cart_xy, next_move.movetype);
            
            // cerr << "Checking Decision " << endl;
            
            for (int r = 0; r< prefix.moves.size(); r++){
                Hex my_hex = board.convertToHex(prefix.carts[r].x , prefix.carts[r].y);	  
                cout << prefix.moves[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }
            
            vector<Hex> my_hex_vec;
            for (int r = 0; r< next_move.cart_xy.size(); r++){
                Hex my_hex = board.convertToHex(next_move.cart_xy[r].x , next_move.cart_xy[r].y);	  
                my_hex_vec.push_back(my_hex);      	
                cout << next_move.movetype[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }
            cout << endl;	

            board.printConfig();
  
        }
    }   
    else if(player == 1) {
    	Tup3 prefix,t;
        Cart opp_c_in, opp_c_fin;
        int countermv = 0;
        while(true) {
        	if (countermv <= 5) countermv ++;
    		if (countermv > 5) {
    			board.my_state = 2;
    		}
    		else {
    			board.my_state = 1;
    		}
        	board.printConfig();
        	int ply = 4;
            string a, s,r,p ;

            MoveVal next_move = DecisionMaker(board, ply, board.my_state);//****************************
            board.execute_move_sequence_my(next_move.cart_xy, next_move.movetype);
            // cerr << "Checking Decision " << endl;

            for (int r = 0; r< prefix.moves.size(); r++){
                Hex my_hex = board.convertToHex(prefix.carts[r].x , prefix.carts[r].y);	  
                cout << prefix.moves[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }

            
            prefix = t;
            vector<Hex> my_hex_vec;
            for (int r = 0; r< next_move.cart_xy.size(); r++){
                Hex my_hex = board.convertToHex(next_move.cart_xy[r].x , next_move.cart_xy[r].y);	  
                my_hex_vec.push_back(my_hex);      	
                cout << next_move.movetype[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }
            cout << endl;	

            // board.printConfig();

            getline(cin, a);
            // cerr << a << endl;
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
		
			board.prev_Opp_move = Tup3(strVec, Cartvec);
            bool found = false;
			for (int r = 0; r< board.prev_Opp_move.moves.size(); r++){
				if (board.prev_Opp_move.moves[r] == "S"){
					opp_c_in = board.prev_Opp_move.carts[r];
					opp_c_fin = board.prev_Opp_move.carts[r+1];
					found = true;
					break;
				}
			}
			board.execute_move_sequence_opp(Hexvec, strVec);
			if (found){
				prefix = board.CheckRowsMadeByOpp( opp_c_in, opp_c_fin, true);

			}

            // board.printConfig();
        }
    }
	
}



