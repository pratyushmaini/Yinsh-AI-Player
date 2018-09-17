//State of the game ://
#include "board.h"



//****************NOT UPDATED PREVIOUS MOVE ANYWHERE -- BOARDDDDDDD UTILITY NOT UPDATEDDDD******************************//
//*****ALSO WHAT ABOUT STATE?????***************************//

MoveVal DecisionMaker(Board board, int ply, int my_state){
    MoveVal temp(INT_MIN);
    MoveVal mv = MaxVal(board, INT_MIN, INT_MAX, ply, my_state, temp);
    // cerr << "Checking Decision " << mv.movetype[0] << " " << mv.cart_xy[0].x << " "<< mv.cart_xy[0].y << endl;
    return mv;
}

MoveVal MaxVal(Board board, float alpha, float beta, int ply, int my_state, MoveVal prev_move){
    // cerr << "Enter MaxVal" <<endl;
    bool my_turn = true;
    if (ply == 0){
        prev_move.utility = board.find_utility();
        return prev_move;
    }
    board.find_children( my_state, my_turn);
    // cerr << "Children Returned, Size: " <<board.children.neighbours.size()<< ", "<<endl;
    if (board.children.neighbours.size() == 0){
        prev_move.utility = board.find_utility();
        return prev_move;
    }
    // MoveVal* ptrMove = new MoveVal(INT_MIN);
    MoveVal my_child;
    for (int i = 0; i < board.children.neighbours.size(); i++){
        board.execute_move_sequence_my(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype ); 
        // cerr << "Looping MaxVal ngb" ;
        // cerr << board.children.neighbours[i].movetype[0] << " " << board.children.neighbours[i].cart_xy[0].x << " " << board.children.neighbours[i].cart_xy[0].y    ;
        // MoveVal* prev_ptr = &board.children.neighbours[i];
        my_child = MinVal(board,alpha,beta, ply - 1, board.children.next_state, board.children.neighbours[i]);//How to find new state??????????????????
        alpha = std::max(alpha,my_child.utility);
        // cerr << "Alpha: "<<alpha<< " Beta: "<<beta<<endl; 
        board.undo_move_sequence_my(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype);
        if (alpha>=beta) {
            // cerr << "PRUNEEEE" <<endl;
            prev_move.movetype = board.children.neighbours[i].movetype;
            prev_move.cart_xy = board.children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
            return prev_move;
        }
        // cerr << "My Child utility" <<my_child.utility<< " movetype: "<<my_child.movetype[0] << " Cartx: " <<my_child.cart_xy[0].x << " Carty: " << my_child.cart_xy[0].y << endl; 
        if (prev_move.utility <= my_child.utility){
            // ptrMove = &my_child;
            prev_move.movetype = board.children.neighbours[i].movetype;
            prev_move.cart_xy = board.children.neighbours[i].cart_xy;
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

MoveVal MinVal(Board board, float alpha, float beta, int ply, int my_state, MoveVal prev_move){
    // cerr << "Enter MinVal" <<endl;
    bool my_turn = false;
    // cerr << "In MinVal" << prev_move.movetype[0] << " " << prev_move.cart_xy[0].x <<" "<< prev_move.cart_xy[0].y <<endl;
    if (ply ==0 ){
        prev_move.utility = board.find_utility();
        return prev_move;
    }
    board.find_children(my_state, my_turn);
    if (board.children.neighbours.size() == 0 ){
        prev_move.utility = board.find_utility();        
        return prev_move;
    }
    // MoveVal* ptrMove = new MoveVal(INT_MAX);
    MoveVal my_child;
    for (int i = 0; i < board.children.neighbours.size(); i++){        
        board.execute_move_sequence_opp(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype );
        // MoveVal* prev_ptr = &board.children.neighbours[i];
        my_child = MaxVal(board,alpha,beta, ply - 1, board.children.next_state, board.children.neighbours[i]);//How to find new state??????????????????
        beta = std::min(beta,my_child.utility);
        board.undo_move_sequence_opp(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype);
        if (alpha>=beta){
            prev_move.movetype = board.children.neighbours[i].movetype;
            prev_move.cart_xy = board.children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
            return prev_move;
        }
        if (prev_move.utility >= my_child.utility){
            prev_move.movetype = board.children.neighbours[i].movetype;
            prev_move.cart_xy = board.children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
        } 
            
    }
    // prev_move.movetype = ptrMove -> movetype;
    // prev_move.cart_xy = ptrMove -> cart_xy;
    // prev_move.utility = ptrMove -> utility;
    return prev_move;
} 



