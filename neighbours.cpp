#include "minimax.h"
#include <vector>
using namespace std;
#include<bits/stdc++.h> 

float Board::find_utility(vector<Cart> ct, vector<string> m, float prev_utility){
	float util;

	return util;
}

Tup3 check_row_vertical(vector<Cart> rings, vector<vector<string>> map, int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    Tup3 t;
    for(int i=0;i<=10;i++)
    {
        if(map[i][x1]=="M") 
            {
                v++;vip=1;
                if(v==5)
                {
                    Cart c1;c1.x=x1;c1.y=i;Cart c2;c2.x=x1;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<rings.size(); i++)
                    {
                        
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(rings[i]);
                    }
                }
            }
        else{v=0;vip=0;}
    }
    return t;
}
Tup3 check_row_horizontal(vector<Cart> rings, vector<vector<string>> map, int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    Tup3 t;
    for(int i=0;i<=10;i++)
    {
        if(map[y1][i]=="M") 
            {
                h++;hip=1;
                if(h==5)
                {
                    Cart c1;c1.x=x1;c1.y=i;Cart c2;c2.x=x1;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<rings.size(); i++)
                    {
                        
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(rings[i]);
                    }
                }
            }
        else{h=0;hip=0;}
    }
    return t;
}
Tup3 check_row_diagonal(vector<Cart> rings, vector<vector<string>> map, int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    Tup3 t;
    for(int i=0;i<10-std::abs(x1-y1);i++)
        {
            if(x1>=y1)
            {
                if(map[i][x1-y1+i]=="M") 
                {
                    h++;hip=1;
                    if(h==5)
                    {
                        Cart c1;c1.x=x1-y1+i;c1.y=i;Cart c2;c2.x=x1-y1+i-5;c2.y=i-5;
                        // for (auto i = rings.begin(); i != rings.end(); ++i)
                        for (int i=0; i<rings.size(); i++)
                        {
                            t.moves.push_back("RS");
                            t.moves.push_back("RE");
                            t.carts.push_back(c1);
                            t.carts.push_back(c2);
                            //map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                            //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                            t.moves.push_back("X");
                            t.carts.push_back(rings[i]);
                        }
                    }
                }
                else{h=0;hip=0;}
            }
            else
            {
                if(map[y1-x1+i][i]=="M") 
                {
                    h++;hip=1;
                    if(h==5)
                    {
                        Cart c1;c1.x=i;c1.y=y1-x1+i;Cart c2;c2.x=i-5;c2.y=y1-x1+i-5;
                        // for (auto i = rings.begin(); i != rings.end(); ++i)
                        for (int i=0; i<rings.size(); i++)
                        {
                            t.moves.push_back("RS");
                            t.moves.push_back("RE");
                            t.carts.push_back(c1);
                            t.carts.push_back(c2);
                            //map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                            //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                            t.moves.push_back("X");
                            t.carts.push_back(rings[i]);
                        }
                    }
                }
                else{h=0;hip=0;}
            }
        }
    return t;
}
Tup3 check_row_all_points(vector<Cart> rings, vector<vector<string>> map, int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    Tup3 non_intersecting_rows;
    if(x1==x2)
    {
        Tup3 temp1=check_row_horizontal(rings,map,x1,y1,x2,y2);
        Tup3 temp2=check_row_diagonal(rings,map,x1,y1,x2,y2);
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp1.moves.begin(),temp1.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp1.carts.begin(),temp1.carts.end());
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp2.moves.begin(),temp2.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp2.carts.begin(),temp2.carts.end());
    }
    else if(y1==y2)
    {
        Tup3 temp1=check_row_vertical(rings,map,x1,y1,x2,y2);
        Tup3 temp2=check_row_diagonal(rings,map,x1,y1,x2,y2);
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp1.moves.begin(),temp1.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp1.carts.begin(),temp1.carts.end());
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp2.moves.begin(),temp2.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp2.carts.begin(),temp2.carts.end());
    }
    else
    {
        Tup3 temp1=check_row_vertical(rings,map,x1,y1,x2,y2);
        Tup3 temp2=check_row_horizontal(rings,map,x1,y1,x2,y2);
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp1.moves.begin(),temp1.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp1.carts.begin(),temp1.carts.end());
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp2.moves.begin(),temp2.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp2.carts.begin(),temp2.carts.end());   
    }
    return non_intersecting_rows;    
}
vector<Tup3> check_row(vector<Cart> rings, vector<vector<string>> map, int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    map[x1][y1]="M";
    map[x2][y2]="R";
    vector<Tup3> output;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    for(int i=0;i<=10;i++)
    {
        if(map[y1][i]=="M") 
            {
                h++;hip=1;
                if(h==5)
                {
                    Cart c1;c1.x=x1;c1.y=i;Cart c2;c2.x=x1;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<rings.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(rings[i]);
                        output.push_back(t);
                    }
                }
            }
        else{h=0;hip=0;}
        if(map[i][x1]=="M") 
            {
                v++;vip=1;
                if(v==5)
                {
                    Cart c1;c1.x=x1;c1.y=i;Cart c2;c2.x=x1;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<rings.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(rings[i]);
                        output.push_back(t);
                    }
                }
            }
        else{v=0;vip=0;}
    }
    for(int i=0;i<10-std::abs(x1-y1);i++)
    {
        if(x1>=y1)
        {
            if(map[i][x1-y1+i]=="M") 
            {
                h++;hip=1;
                if(h==5)
                {
                    Cart c1;c1.x=x1-y1+i;c1.y=i;Cart c2;c2.x=x1-y1+i-5;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<rings.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(rings[i]);
                        output.push_back(t);
                    }
                }
            }
            else{h=0;hip=0;}
        }
        else
        {
            if(map[y1-x1+i][i]=="M") 
            {
                h++;hip=1;
                if(h==5)
                {
                    Cart c1;c1.x=i;c1.y=y1-x1+i;Cart c2;c2.x=i-5;c2.y=y1-x1+i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<rings.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(rings[i]);
                        output.push_back(t);
                    }
                }
            }
            else{h=0;hip=0;}
        }
    }
    return output;
}
vector<MoveVal> Board::find_neighbours(Cart c, int dir, bool my_turn)//c--> position of ring to be moved
{	
	float prev_utility;
	int x,y;
	if(dir==1)
	{
	    x=c.x;
	    y=c.y+1;
	}
	else if(dir==2)
	{
	    x=c.x;
	    y=c.y-1;
	}
	else if(dir==3)
	{
	    x=c.x+1;
	    y=c.y;
	}
	else if(dir==4)
	{
	    x=c.x -1 ;
	    y=c.y;
	}
	else if(dir==5) 
	{
	    x=c.x+ 1;
	    y=c.y+1;
	}
	else if(dir==6)
	{
	    x=c.x-1;
	    y=c.y-1;
	}

    int t=0;//t=1--> a marker has been encountered
    MoveVal mvl;
    Children ch;
    while(!(mapping[y][x]=="R" ||mapping[y][x]=="RO" ||mapping[y][x]=="I"))
    {
        if(mapping[y][x]=="E" && t==0)
        {
            vector<string> m;
            vector<Cart> ct;
            Cart r;
            r.x=x;r.y=y;
            m.push_back("S");
            m.push_back("M");
            ct.push_back(c);
            ct.push_back(r);
            prev_utility = utility_board;

            execute_move_sequence(ct,m,my_turn);
            vector<Tup3> t_vec = check_row(RingPos,mapping,c.x,c.y,x,y);
            
            if(t_vec.size() > 0)
            {
                for(int j=0;j<t_vec.size();j++)
                {
                    m.insert(m.end(),t_vec[j].moves.begin(),t_vec[j].moves.end());
                    ct.insert(ct.end(),t_vec[j].carts.begin(),t_vec[j].carts.end());          
                    mvl.movetype = m;
                    mvl.cart_xy = ct;


             		execute_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);
                    mvl.utility=find_utility(ct, m, prev_utility);//------------------------------------Make this-----------------------------------------
                    ch.neighbours.push_back(mvl);
                    m.pop_back();m.pop_back();m.pop_back();
                    ct.pop_back();ct.pop_back();ct.pop_back();
                    undo_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);

                }
            }
            
            else
            {
	            mvl.movetype = m;
	            mvl.cart_xy = ct;
	            mvl.utility=find_utility(ct, m, prev_utility);//------------------------------------Make this-----------------------------------------
	            ch.neighbours.push_back(mvl);
	        }
	        undo_move_sequence(ct,m, my_turn);
            if(dir==1)
			{
			    y++;
			}
			else if(dir==2)
			{
			    y--;
			}
			else if(dir==3)
			{
			    x++;
			}
			else if(dir==4)
			{
			    x--;
			}
			else if(dir==5)
			{
			    x++; y++;
			}
			else if(dir==6)
			{
			    x--; y--;
			}
        }
        else if(mapping[y][x]=="M" || mapping[y][x]=="MO")
        {
            t=1;
            if(dir==1)
			{
			    y++;
			}
			else if(dir==2)
			{
			    y--;
			}
			else if(dir==3)
			{
			    x++;
			}
			else if(dir==4)
			{
			    x--;
			}
			else if(dir==5)
			{
			    x++; y++;
			}
			else if(dir==6)
			{
			    x--; y--;
			}
        }
        else if(mapping[y][x]=="E" && t==1)
        {
            vector<string> m;
            vector<Cart> ct;
            Cart r;
            r.x=x;r.y=y;
            m.push_back("S");
            m.push_back("M");
            ct.push_back(c);
            ct.push_back(r);
            prev_utility = utility_board;

            execute_move_sequence(ct,m, my_turn);
            vector<Tup3> t_vec = check_row(RingPos,mapping,c.x,c.y,x,y);
            
            if(t_vec.size() > 0)
            {
                for(int j=0;j<t_vec.size();j++)
                {
                    m.insert(m.end(),t_vec[j].moves.begin(),t_vec[j].moves.end());
                    ct.insert(ct.end(),t_vec[j].carts.begin(),t_vec[j].carts.end());          
                    mvl.movetype = m;
                    mvl.cart_xy = ct;
             		execute_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);
                    mvl.utility=find_utility(ct, m, prev_utility);//------------------------------------Make this-----------------------------------------
                    ch.neighbours.push_back(mvl);
                    m.pop_back();m.pop_back();m.pop_back();
                    ct.pop_back();ct.pop_back();ct.pop_back();
                    undo_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);

                }
            }
            
            else
            {
	            mvl.movetype = m;
	            mvl.cart_xy = ct;
	            mvl.utility=find_utility(ct, m, prev_utility);//------------------------------------Make this-----------------------------------------
	            ch.neighbours.push_back(mvl);
	        }
	        undo_move_sequence(ct,m, my_turn);
            break;  
        }
    }
    return ch.neighbours;
}

vector<MoveVal> Board::moveRing(bool my_turn)
{
    vector<Cart> rings= RingPos;
    Cart init_pos;
    vector<MoveVal> padosi;
    for (int i=0; i < rings.size(); i++) 
    {
    	for(int j=1;j<=6;j++)
    	{
	        vector<MoveVal> p1=find_neighbours(rings[i],j, my_turn);
	        padosi.insert(padosi.end(),p1.begin(),p1.end());
	    }
    }
    return padosi; 
}


vector<MoveVal> Board::placeRing(bool my_turn){
//////////////////////////////////////***********************************************
   cout << "Place Ring Called" <<endl;
   MoveVal move;
   float prev_utility;
   vector<MoveVal> all_possible_moves;
   if(RingPos.size()<=4)
   {
       for(int x=4;x<=6;x++)
       {
           for(int y=4;y<=6;y++)
           {
               if(mapping[y][x]=="E")
               {
                   Cart c;
                   c.x=x;
                   c.y=y;
                   move.movetype.push_back("P");
                   move.cart_xy.push_back(c);
                   prev_utility = utility_board;
                   execute_move_sequence(move.cart_xy, move.movetype, my_turn);
                   move.utility=find_utility(move.cart_xy, move.movetype, prev_utility);
                   all_possible_moves.push_back(move);
               }
           }
       }
   }
   else
   {
       for(int y=0;y<=3;y++)
       {
           if(mapping[y+6][10]=="E")
           {
               Cart c;
               c.x=10;
               c.y=y+6;
               move.movetype.push_back("P");
               move.cart_xy.push_back(c);
               prev_utility = utility_board;
               execute_move_sequence(move.cart_xy, move.movetype, my_turn);
               move.utility=find_utility( move.cart_xy, move.movetype, prev_utility);
               all_possible_moves.push_back(move);
           }
           if(mapping[y+1][0]=="E")
           {
               Cart c;
               c.x=0;
               c.y=y+1;
               move.movetype.push_back("P");
               move.cart_xy.push_back(c);
               prev_utility = utility_board;
               execute_move_sequence(move.cart_xy, move.movetype, my_turn);
               move.utility=find_utility(move.cart_xy, move.movetype, prev_utility);
               all_possible_moves.push_back(move);
           }
       }
   }
   return all_possible_moves;
}

 

void Board::find_children(int playerstate, bool my_turn)
{
    if(playerstate==1)
    {
        vector<MoveVal> move=placeRing(my_turn);
        if(RingPos.size()==5) playerstate=2;//------------------------------------------check syntax------------------------------
        children.neighbours = move;
        children.next_state = playerstate;

    }
    if(playerstate==2)
    {
        vector<MoveVal> p=moveRing(my_turn);
        children.neighbours = p;
        children.next_state = 2;

    }
    // if(playerstate==3)
    // {
    // }
}