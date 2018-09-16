
#include "player.h"
#include <boost/algorithm/string.hpp>
 


void Player::play(){
	board.printConfig();
	if(player == 2) {
    	while(true) {
        	cerr <<"Play"<<endl;
            string a, s,r,p ;
            // getline(cin,s);
            // cin>>s>>r>>p;
            cin.ignore(); 
            getline(cin, a);
            cerr << a << endl;
			vector<string> results;
			boost::split(results, a, [](char c){return c == ' ';});
            cerr << s << endl;
            vector<Hex> Hexvec;
            vector<string> strVec;
            for (int q=0; q<results.size(); q+=3){
            	s = results[q];
            	r = results[q+1];
            	p = results[q+2];
            	Hex tup(stoi(r),stoi(p));
				Hexvec.push_back(tup);
				strVec.push_back(s);
            }
		
			board.execute_move_sequence_opp(Hexvec, strVec);

            board.printConfig();

            int ply = 1;
            if (board.my_state == 1 && board.RingPos.size() == 5){
            	board.my_state = 2;
            	ply = 4;
            }
            if (board.opp_state == 1 && board.RingPosOpp.size() == 5){
            	board.opp_state = 2;
            	ply = 4;
            }
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

            board.printConfig();

            
            cerr << "OUTPUT PRINT HERE IN HEX FORM" <<endl; 
        }
    }   
    else if(player == 1) {
        while(true) {
        	cerr <<"Play"<<endl;
            string a, s,r,p ;
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
            cerr << "Checking Decision " << endl;
            vector<Hex> my_hex_vec;
            for (int r = 0; r< next_move.cart_xy.size(); r++){
                Hex my_hex = board.convertToHex(next_move.cart_xy[r].x , next_move.cart_xy[r].y);	  
                my_hex_vec.push_back(my_hex);      	
                cout << next_move.movetype[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }
            cout << endl;	

            board.printConfig();

            // cin>>s>>r>>p;
            cin.ignore(); 
            getline(cin, a);
            cerr << a << endl;
			vector<string> results;
			boost::split(results, a, [](char c){return c == ' ';});
            cerr << s << endl;
            vector<Hex> Hexvec;
            vector<string> strVec;
            for (int q=0; q<results.size(); q+=3){
            	s = results[q];
            	r = results[q+1];
            	p = results[q+2];
            	Hex tup(stoi(r),stoi(p));
				Hexvec.push_back(tup);
				strVec.push_back(s);
            }
		
			board.execute_move_sequence_opp(Hexvec, strVec);

            board.printConfig();
            cerr << "OUTPUT PRINT HERE IN HEX FORM" <<endl; 
        }
    }
	
}



