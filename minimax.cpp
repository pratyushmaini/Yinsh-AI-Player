//State of the game ://
#include "minimax.h"
#include <vector>
using namespace std;
#include<bits/stdc++.h> 



float utility(Board board, MoveVal prev_move){
	return prev_move.utility;
}

MoveVal DecisionMaker(Board board, int ply, int my_state){
    MoveVal mv = MaxVal(board, INT_MIN, INT_MAX, ply, my_state, NULL);//************************************8***
    return mv;
}
//MaxVal should return the action P 0 1 etc, the value



MoveVal MaxVal(Board board, float alpha, float beta, int ply, int my_state, MoveVal prev_move){
    Children child = children(board, my_state);
    if (child.neighbours.size() == 0 || ply == 0){
        return utility(board, prev_move);
    }
    MoveVal Max_move(INT_MIN);
    for (int i = 0; i < child.neighbours.size(); i++){
        board.execute_move_sequence(child.neighbours[i].cart_xy, child.neighbours[i].movetype );        
        MoveVal my_child = MinVal(board,alpha,beta, ply - 1, child.next_state, child.neighbours[i]);//How to find new state??????????????????
        alpha = std::max(alpha,my_child.utility);
        board.undo_move_sequence(child.neighbours[i].cart_xy, child.neighbours[i].movetype);
        if (alpha>=beta) {
            return my_child;
        }        
        if (Max_move.utility <= my_child.utility){
            // *Max_move = *my_child; //*************************************************************************8
        }
    }
    return Max_move; //?????????????????????
} 

MoveVal MinVal(Board board, float alpha, float beta, int ply, int my_state, MoveVal prev_move){
    Children child = children(board, my_state);
    if (child.neighbours.size() == 0 || ply == 0){
        return utility(board, prev_move);
    }
    MoveVal Min_move(INT_MAX);
    for (int i = 0; i < child.neighbours.size(); i++){        
        board.execute_move_sequence(child.neighbours[i].cart_xy, child.neighbours[i].movetype );
        MoveVal my_child = MaxVal(board,alpha,beta, ply - 1, child.next_state, child.neighbours[i]);//How to find new state??????????????????
        beta = std::min(beta,my_child.utility);
        board.undo_move_sequence(child.neighbours[i].cart_xy, child.neighbours[i].movetype);
        if (alpha>=beta){
            return my_child;
        }
        if (Min_move.utility >= my_child.utility){
            // *Min_move = *my_child;//**************************************************************************8
        } 
            
    }
return Min_move; 
} 



