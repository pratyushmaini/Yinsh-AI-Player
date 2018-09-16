//State of the game ://
#include "minimax.h"
#include <vector>
using namespace std;
#include<bits/stdc++.h> 


//****************NOT UPDATED PREVIOUS MOVE ANYWHERE******************************//

MoveVal DecisionMaker(Board board, int ply, int my_state){
    MoveVal* temp = new MoveVal(board.utility_board);
    MoveVal* mv_ptr = MaxVal(board, INT_MIN, INT_MAX, ply, my_state, temp);//************************************8***
    cout << mv_ptr -> movetype[0] << " " << mv_ptr -> cart_xy[0].x << " "<< mv_ptr -> cart_xy[0].y << endl;
    return *mv_ptr;
}
//MaxVal should return the action P 0 1 etc, the value

MoveVal* MaxVal(Board board, float alpha, float beta, int ply, int my_state, MoveVal* prev_move){
    cout << "Enter MaxVal" <<endl;
    bool my_turn = true;
    board.find_children( my_state, my_turn);
    cout << "Children Returned, Size: " <<board.children.neighbours.size()<< ", "<<endl;
    if (board.children.neighbours.size() == 0 || ply == 0){
        return prev_move;
    }
    MoveVal Max_move(INT_MIN);
    MoveVal* ptrMove = &Max_move;
    for (int i = 0; i < board.children.neighbours.size(); i++){
        board.execute_move_sequence_my(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype ); 
        cout << board.children.neighbours[i].movetype[0] << " " << board.children.neighbours[i].cart_xy[0].x << " " << board.children.neighbours[i].cart_xy[0].y    ;
        MoveVal* prev_ptr = &board.children.neighbours[i];
        MoveVal* my_child = MinVal(board,alpha,beta, ply - 1, board.children.next_state, prev_ptr);//How to find new state??????????????????
        alpha = std::max(alpha,my_child -> utility);
        board.undo_move_sequence_my(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype);
        if (alpha>=beta) {
            return my_child;
        }        
        if (ptrMove->utility <= my_child -> utility){
            ptrMove = my_child; //*************************************************************************8
        }
    }
    return ptrMove; //?????????????????????
} 

MoveVal* MinVal(Board board, float alpha, float beta, int ply, int my_state, MoveVal* prev_move){
    cout << "Enter MinVal" <<endl;
    bool my_turn = false;
    cout << "In MinVal" << prev_move -> movetype[0] << " " << prev_move -> cart_xy[0].x <<" "<< prev_move -> cart_xy[0].y <<endl;
    if (ply ==0 ){
        return prev_move;
    }
    board.find_children(my_state, my_turn);
    if (board.children.neighbours.size() == 0 ){
        return prev_move;
    }
    MoveVal Min_move(INT_MAX);
     MoveVal* ptrMove = &Min_move;
    for (int i = 0; i < board.children.neighbours.size(); i++){        
        board.execute_move_sequence_opp(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype );
        MoveVal* prev_ptr = &board.children.neighbours[i];
        MoveVal* my_child = MaxVal(board,alpha,beta, ply - 1, board.children.next_state, prev_ptr);//How to find new state??????????????????
        beta = std::min(beta,my_child -> utility);
        board.undo_move_sequence_opp(board.children.neighbours[i].cart_xy, board.children.neighbours[i].movetype);
        if (alpha>=beta){
            return my_child;
        }
        if (ptrMove->utility >= my_child -> utility){
            ptrMove = my_child;//**************************************************************************8
        } 
            
    }
return ptrMove; 
} 



