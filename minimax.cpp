//State of the game ://
#include "board.h"

//****************NOT UPDATED PREVIOUS MOVE ANYWHERE -- BOARDDDDDDD UTILITY NOT UPDATEDDDD******************************//
//*****ALSO WHAT ABOUT STATE?????***************************//

MoveVal Board::DecisionMaker(int ply, int my_state){
    MoveVal temp(INT_MIN);
    MoveVal mv;
    if (my_state == 2){
        mv = MaxVal(INT_MIN, INT_MAX, ply, 2, temp);
    }
    else {
        mv = placeRing(true)[0];
    }
    // cerr << "Checking Decision " ;
    // cerr << mv.movetype[0] << " " << mv.cart_xy[0].x << " "<< mv.cart_xy[0].y << endl;
    return mv;
}

MoveVal Board::MaxVal(float alpha, float beta, int ply, int my_state, MoveVal prev_move){
    // cerr << "Ply Maxval "<< ply<< endl;
    // printConfig();
    // cerr << "Enter MaxVal" <<endl;
    bool my_turn = true;
    if (ply == 0){
        prev_move.utility = find_utility();
        // cerr << "Ply 0 ret" << endl;
        return prev_move;
    }
    Children my_children = find_children( my_state, my_turn);
    // cerr << "After Find Children" << endl;
    // printConfig();
    // cerr << "Children Returned, Size: " <<my_children.neighbours.size()<< ", "<<endl;
    if (my_children.neighbours.size() == 0){
        prev_move.utility = find_utility();
        return prev_move;
    }
    // MoveVal* ptrMove = new MoveVal(INT_MIN);
    MoveVal my_child;
    for (int i = 0; i < my_children.neighbours.size(); i++){

        execute_move_sequence_my(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype ); 
        // cerr << "Looping MaxVal ngb" ;
        // cerr << my_children.neighbours[i].movetype[0] << " " << my_children.neighbours[i].cart_xy[0].x << " " << my_children.neighbours[i].cart_xy[0].y    ;
        // MoveVal* prev_ptr = &my_children.neighbours[i];
        my_child = MinVal(alpha,beta, ply - 1, my_children.next_state, my_children.neighbours[i]);//How to find new state??????????????????
        alpha = std::max(alpha,my_child.utility);
        // cerr << "Alpha: "<<alpha<< " Beta: "<<beta<<endl; 
        undo_move_sequence_my(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype);
        if (alpha>=beta) {
            // cerr << "PRUNEEEE" <<endl;
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
            return prev_move;
        }
        // cerr << "My Child utility" <<my_child.utility<< " movetype: "<<my_child.movetype[0] << " Cartx: " <<my_child.cart_xy[0].x << " Carty: " << my_child.cart_xy[0].y << endl; 
        if (prev_move.utility <= my_child.utility){
            // ptrMove = &my_child;
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
            // cerr << "Prev Move utility: " ;
            // cerr << prev_move.utility<<" movetype: "<<prev_move.movetype[0] << " Cartx: " <<prev_move.cart_xy[0].x << " Carty: " <<prev_move.cart_xy[0].y << endl;        

        }
    }
    // cerr << "Out of Loop; Pointer Move utility: ";
    // prev_move.movetype = ptrMove -> movetype;
    // prev_move.cart_xy = ptrMove -> cart_xy;
    // prev_move.utility = ptrMove -> utility;
    return prev_move;
}

MoveVal Board::MinVal(float alpha, float beta, int ply, int my_state, MoveVal prev_move){
    // cerr << "Ply MinVal "<< ply<< endl;
    // printConfig();
    // cerr << "Enter MinVal" <<endl;
    bool my_turn = false;
    // cerr << "In MinVal" << prev_move.movetype[0] << " " << prev_move.cart_xy[0].x <<" "<< prev_move.cart_xy[0].y <<endl;
    if (ply ==0 ){
        prev_move.utility = find_utility();
        return prev_move;
    }
    Children my_children = find_children(my_state, my_turn);
    if (my_children.neighbours.size() == 0 ){
        prev_move.utility = find_utility();        
        return prev_move;
    }
    // cerr << "After Find Children" << endl;
    // printConfig();
    // MoveVal* ptrMove = new MoveVal(INT_MAX);
    MoveVal my_child;
    for (int i = 0; i < my_children.neighbours.size(); i++){
        execute_move_sequence_opp(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype );
        // MoveVal* prev_ptr = &my_children.neighbours[i];
        my_child = MaxVal(alpha,beta, ply - 1, my_children.next_state, my_children.neighbours[i]);//How to find new state??????????????????
        beta = std::min(beta,my_child.utility);
        undo_move_sequence_opp(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype);
        if (alpha>=beta){
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
            return prev_move;
        }
        if (prev_move.utility >= my_child.utility){
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
        } 
            
    }
    // prev_move.movetype = ptrMove -> movetype;
    // prev_move.cart_xy = ptrMove -> cart_xy;
    // prev_move.utility = ptrMove -> utility;
    return prev_move;
} 



