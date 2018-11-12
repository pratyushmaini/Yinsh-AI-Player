#include "board.h"

int nodes_explored = 0;

MoveVal Board::DecisionMaker(int ply, int my_state, bool util_type){
    MoveVal mv;
    nodes_explored = 0;
    if (my_state == 2){
        mv = MaxVal(INT_MIN, INT_MAX, ply, util_type);//, nodes_explored);
        // cerr << "FINAL UTIL" << mv.utility << endl;
    }
    else {
        mv = placeRing(true)[0];
    }
    // cerr << nodes_explored << " = nodes_explored" << endl;
    // cerr << "RingPosOpp Size"

    return mv;
}

MoveVal Board::MaxVal(float alpha, float beta, int ply, bool util_type){// int nodes_explored){
    nodes_explored ++;
    // if (ply == 4)
        // cerr << "\n\n\nENTER MAXVAL\n\n\n" << endl;
    MoveVal prev_move(INT_MIN);
    bool my_turn = true;
    if (ply == 0 || RingPos.size() <= (rings_max - 3) || RingPosOpp.size() <= (rings_max - 3)){
        prev_move.utility = find_utility_master(util_type);
        // if (ply == 4)
            // cerr << prev_move.utility << " = MAXVAL CHOICE" << endl;
        return prev_move;
    }
    Children my_children = find_children( my_state, my_turn);
    // cerr << "After Find Children Max VAL" << endl;

    if (my_children.neighbours.size() == 0 ){// || rings_max-RingPos.size() >= 3 || rings_max-RingPosOpp.size() >= 3){
        prev_move.utility = find_utility_master(util_type);
        // if (ply == 4)
            // cerr << prev_move.utility << " = MAXVAL CHOICE" << endl;
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
        // if (ply == 4){
        //         cerr << my_child.utility << " = MAXVAL CHOICE" << endl;
        //             // for (int w = 0; w< my_children.neighbours.size(); w++){
        //         for (int j = 0; j < my_children.neighbours[i].movetype.size(); j++)
        //         {
        //             cerr << my_children.neighbours[i].movetype[j] << " " << my_children.neighbours[i].cart_xy[j].x << " "<< my_children.neighbours[i].cart_xy[j].y ;
        //         }
        //         cerr << endl;
        // }               
                  // }
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
    // if (ply == 4)
    //     cerr << prev_move.utility << " = MAXVAL CHOICE" << endl;
    return prev_move;
}

MoveVal Board::MinVal(float alpha, float beta, int ply, bool util_type){//, int nodes_explored){
    // cerr << "\n\n\nENTER MINVAL\n\n\n" << endl;
    nodes_explored ++;
    MoveVal prev_move(INT_MAX);
    bool my_turn = false;
    if (ply ==0 || RingPos.size()<= rings_max - 3 || RingPosOpp.size() <= rings_max - 3){
        prev_move.utility = find_utility_master(util_type);
        // cerr << prev_move.utility << " = MINVAL CHOICE" << endl;
        return prev_move;
    }
    Children my_children = find_children(my_state, my_turn);
    if (my_children.neighbours.size() == 0 || rings_max-RingPos.size() >= 3 || rings_max-RingPosOpp.size() >= 3){
        prev_move.utility = find_utility_master(util_type);
        // cerr << prev_move.utility << " = MINVAL CHOICE" << endl;
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
        // if (ply == 3){
        //         cerr << my_child.utility << " = MINVAL CHOICE" << endl;
        //             // for (int w = 0; w< my_children.neighbours.size(); w++){
        //         for (int j = 0; j < my_children.neighbours[i].movetype.size(); j++)
        //         {
        //             cerr << my_children.neighbours[i].movetype[j] << " " << my_children.neighbours[i].cart_xy[j].x << " "<< my_children.neighbours[i].cart_xy[j].y ;
        //         }
        //         cerr << endl;
        //         cerr << "Alpha "<< alpha << " Beta " <<beta << endl;
        // }  
        undo_move_sequence_opp(my_children.neighbours[i].cart_xy, my_children.neighbours[i].movetype);
        if (alpha>=beta){
            // cerr << "PRUNEEEE " << endl;
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            // if (ply == 3)
            //     cerr << my_child.utility << " Pruning util" << endl;
            prev_move.utility = my_child.utility;
            // cerr << prev_move.utility << " = MINVAL CHOICE" << endl;
            return prev_move;
        }
        if (prev_move.utility > my_child.utility){
            prev_move.movetype = my_children.neighbours[i].movetype;
            prev_move.cart_xy = my_children.neighbours[i].cart_xy;
            prev_move.utility = my_child.utility;
        } 
    }
    // cerr << prev_move.utility << " = MINVAL CHOICE" << endl;
    return prev_move;
} 



