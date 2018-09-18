
#include "player.h"
 
void Player::play_2( int ply, int countermv){ //Counts if 5 moves done?
    while(true) {
        // board.printConfig();
        cerr << "MarkersMy: " << board.markersMy << "MarkersOpp: " << board.markersOpp << endl;
        if (countermv <= 5) countermv ++;
        if (countermv > 5) {
            board.my_state = 2;
        }
        else {
            board.my_state = 1;
        }
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
        cerr << "After Opp move: " << endl;
        // board.printConfig();
        cerr << "MarkersMy: " << board.markersMy << "MarkersOpp: " << board.markersOpp << " ending\n";
        
        // cerr << "Opp move executed" << endl;
        Tup3 prefix;
        if (found){
            prefix = board.CheckRowsMadeByOpp(opp_c_in, opp_c_fin, true);
            // 
        }
        
        // cerr << "Checking Decision " << endl;
        int checker = 0;
        for (int r = 0; r<prefix.moves.size(); r+=3){///**************************FORCING 3 prefix.moves.size()
            checker ++;
            // cerr << "Row made BY OPP" << endl;
            if(board.check_if_row(prefix.carts[r].x,
                            prefix.carts[r].y,
                            prefix.carts[r+1].x,
                            prefix.carts[r+1].y,
                            prefix.carts[r+2].x,
                            prefix.carts[r+2].y,
                            true) == 0){
                for (int l=0; l<3; l++){
                    board.execute_move_my(prefix.carts[r+l], prefix.moves[r+l]);
                    Hex my_hex = board.convertToHex(prefix.carts[r+l].x , prefix.carts[r+l].y);   
                    cout << prefix.moves[r+l] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
                }
                
            }            
            if(board.RingPos.size() == 2) break;
            // if (checker == 3) break;
        }
        
        if (board.RingPos.size() > 2  || board.my_state == 1){
            int markers_opp_saved = board.markersOpp;
            MoveVal next_move = board.DecisionMaker( ply, board.my_state);//****************************
            board.markersOpp = markers_opp_saved;
            cerr << "MarkersMy: " << board.markersMy << "MarkersOpp: " << board.markersOpp << " above util\n";

            cerr << "Utility " << next_move.utility <<" end\n";
            board.execute_move_sequence_my(next_move.cart_xy, next_move.movetype);
            vector<Hex> my_hex_vec;
            for (int r = 0; r< next_move.cart_xy.size(); r++){
                Hex my_hex = board.convertToHex(next_move.cart_xy[r].x , next_move.cart_xy[r].y);     
                my_hex_vec.push_back(my_hex);       
                cout << next_move.movetype[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
            }
        } 
        cout << endl;   

        cerr << "After My move: " << endl;
    }
}

void Player::play(){

	if(player == 2) {
        int ply = 4;
        play_2(ply,0);		
    }   
    else if(player == 1) {
        int ply = 4;
        MoveVal next_move = board.DecisionMaker( ply, 1);
        board.execute_move_sequence_my(next_move.cart_xy, next_move.movetype);
        vector<Hex> my_hex_vec;
        for (int r = 0; r< next_move.cart_xy.size(); r++){
            Hex my_hex = board.convertToHex(next_move.cart_xy[r].x , next_move.cart_xy[r].y);     
            my_hex_vec.push_back(my_hex);       
            cout << next_move.movetype[r] << " " <<my_hex.ring << " " << my_hex.pos<< " ";
        }

        cout << endl;   
        play_2(ply,1);
    }
}
