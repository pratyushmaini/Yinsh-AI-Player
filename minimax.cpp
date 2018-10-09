#include "board.h"

MoveVal Board::DecisionMaker(int ply, int my_state){
    MoveVal mv;
    if (my_state == 2){
        mv = MaxVal(INT_MIN, INT_MAX, ply);
    }
    else {
        mv = placeRing(true)[0];
    }
    return mv;
}

MoveVal Board::MaxVal(float alpha, float beta, int ply){
    MoveVal prev_move(INT_MIN);
    bool my_turn = true;
    if (ply == 0 || RingPos.size() <= 2 || RingPosOpp.size() <= 2){
        prev_move.utility = find_utility();
        return prev_move;
    }
    Children my_children = find_children( my_state, my_turn);
    if (my_children.neighbours.size() == 0  || 5 -RingPos.size() >= 3 || 5 -RingPosOpp.size() >= 3){
        prev_move.utility = find_utility();
        return prev_move;
    }
    MoveVal my_child;
    for (int i = 0; i < my_children.neighbours.size(); i++){

        execute_move_sequence_my(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype ); 
        my_child = MinVal(alpha,beta, ply - 1);//How to find new state??????????????????
        alpha = std::max(alpha,my_child.utility);
        undo_move_sequence_my(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype);
        if (alpha>=beta) {
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

MoveVal Board::MinVal(float alpha, float beta, int ply){
    MoveVal prev_move(INT_MAX);
    bool my_turn = false;
    if (ply ==0 || RingPos.size()<=2 || RingPosOpp.size() <= 2){
        prev_move.utility = find_utility();
        return prev_move;
    }
    Children my_children = find_children(my_state, my_turn);
    if (my_children.neighbours.size() == 0 || 5 -RingPos.size() >= 3 || 5 -RingPosOpp.size() >= 3){
        prev_move.utility = find_utility();        
        return prev_move;
    }
    MoveVal my_child;
    for (int i = 0; i < my_children.neighbours.size(); i++){
        execute_move_sequence_opp(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype );
        my_child = MaxVal(alpha,beta, ply - 1);//How to find new state??????????????????
        beta = std::min(beta,my_child.utility);
        undo_move_sequence_opp(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype);
        if (alpha>=beta){
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
    return prev_move;
} 



