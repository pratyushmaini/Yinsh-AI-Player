#include "board.h"

int nodes_explored = 0;

MoveVal Board::DecisionMaker(int ply, int my_state, bool util_type){
    MoveVal mv;
    nodes_explored = 0;
    if (my_state == 2){
        mv = MaxVal(INT_MIN, INT_MAX, ply, util_type);//, nodes_explored);
    }
    else {
        mv = placeRing(true)[0];
    }
    cerr << nodes_explored << " = nodes_explored" << endl;
    return mv;
}

MoveVal Board::MaxVal(float alpha, float beta, int ply, bool util_type){// int nodes_explored){
    nodes_explored ++;
    MoveVal prev_move(INT_MIN);
    bool my_turn = true;
    if (ply == 0 || RingPos.size() <= (rings_max - 3) || RingPosOpp.size() <= (rings_max - 3)){
        prev_move.utility = find_utility_master(util_type);
        return prev_move;
    }
    Children my_children = find_children( my_state, my_turn);
    // cerr << "After Find Children Max VAL" << endl;

    if (my_children.neighbours.size() == 0  || rings_max-RingPos.size() >= 3 || rings_max-RingPosOpp.size() >= 3){
        prev_move.utility = find_utility_master(util_type);
        return prev_move;
    }

    /////////////************************************************************************///////////////////////////////////
    for (int w = 0; w< my_children.neighbours.size(); w++){
        execute_move_sequence_my(my_children.neighbours[w].cart_xy, my_children.neighbours[w].movetype);
        my_children.neighbours[w].utility = find_utility_master(false);
        undo_move_sequence_my(my_children.neighbours[w].cart_xy, my_children.neighbours[w].movetype);
    }
    std::sort(my_children.neighbours.rbegin(), my_children.neighbours.rend());
    /////////////************************************************************************///////////////////////////////////

    
    MoveVal my_child;
    for (int i = 0; i < my_children.neighbours.size(); i++){

        execute_move_sequence_my(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype ); 
        my_child = MinVal(alpha,beta, ply - 1, util_type);// nodes_explored);//How to find new state??????????????????
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
        if (prev_move.utility < my_child.utility){
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
        }
    }
    return prev_move;
}

MoveVal Board::MinVal(float alpha, float beta, int ply, bool util_type){//, int nodes_explored){
    nodes_explored ++;
    MoveVal prev_move(INT_MAX);
    bool my_turn = false;
    if (ply ==0 || RingPos.size()<= rings_max - 3 || RingPosOpp.size() <= rings_max - 3){
        prev_move.utility = find_utility_master(util_type);
        return prev_move;
    }
    Children my_children = find_children(my_state, my_turn);
    if (my_children.neighbours.size() == 0 || rings_max-RingPos.size() >= 3 || rings_max-RingPosOpp.size() >= 3){
        prev_move.utility = find_utility_master(util_type);
        return prev_move;
    }
    // cerr << "After Find Children MinVal" << endl;

    /////////////************************************************************************///////////////////////////////////
    for (int w = 0; w< my_children.neighbours.size(); w++){
        execute_move_sequence_opp(my_children.neighbours[w].cart_xy, my_children.neighbours[w].movetype);
        my_children.neighbours[w].utility = find_utility_master(false);
        undo_move_sequence_opp(my_children.neighbours[w].cart_xy, my_children.neighbours[w].movetype);
    }

    std::sort(my_children.neighbours.begin(), my_children.neighbours.end());
    /////////////************************************************************************///////////////////////////////////

    MoveVal my_child;
    for (int i = 0; i < my_children.neighbours.size(); i++){
        execute_move_sequence_opp(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype );
        my_child = MaxVal(alpha,beta, ply - 1,util_type);//, nodes_explored);//How to find new state??????????????????
        beta = std::min(beta,my_child.utility);
        undo_move_sequence_opp(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype);
        if (alpha>=beta){
            // cerr << "PRUNEEEE " << endl;
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
            return prev_move;
        }
        if (prev_move.utility > my_child.utility){
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
        } 
    }
    return prev_move;
} 



