#include "board.h"    


float Board::utility_check_row_vertical(  int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    float utility;
    for(int i=0;i<=10;i++)
    {
        if(mapping[i][x1]=="M") 
        {
            v++;
        }
        else
        {
            if(v==1)
            utility+=1;
            else
            utility+=v*2;    
            v=0;
        }
    }
    return utility;
}
float Board::utility_check_row_horizontal(  int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    float utility;
    for(int i=0;i<=10;i++)
    {
        if(mapping[y1][i]=="M") 
        {
            h++;
        }
        else
        {
            if(h==1)
            utility+=1;
            else
            utility+=h*2;    
            h=0;
        }
    }
    return utility;
}
float Board::utility_check_row_diagonal(  int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    float utility;
    for(int i=0;i<10-std::abs(x1-y1);i++)
        {
            if(x1>=y1)
            {
                if(mapping[i][x1-y1+i]=="M") 
                {
                    h++;
                }
                else
                {
                    if(h==1)
                    utility+=1;
                    else
                    utility+=h*2;    
                    h=0;
                }
            }
            else
            {
                if(mapping[y1-x1+i][i]=="M") 
                {
                    v++;
                }
                else
                {
                    if(v==1)
                    utility+=1;
                    else
                    utility+=v*2;    
                    v=0;
                }
            }
        }
    return utility;
}
float Board::utility_check_row_all_points(  int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    float utility;
    if(x1==x2)
    {
        utility+=utility_check_row_horizontal(x1,y1,x2,y2);
        utility+=utility_check_row_diagonal(x1,y1,x2,y2);
    }
    else if(y1==y2)
    {
        utility+=utility_check_row_vertical(x1,y1,x2,y2);
        utility+=utility_check_row_diagonal(x1,y1,x2,y2);
        
    }
    else
    {
        utility+=utility_check_row_vertical(x1,y1,x2,y2);
        utility+=utility_check_row_horizontal(x1,y1,x2,y2);
    }
    return utility;    
}
float Board::utility_check_row( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    float utility;
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    vector<Tup3> output;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    for(int i=0;i<=10;i++)
    {
        if(mapping[y1][i]=="M") 
        {
            h++;
        }
        else
        {
            if(h==1)
            utility+=1;
            else
            utility+=h*2;    
            h=0;
        }
        if(mapping[i][x1]=="M") 
        {
            v++;       
        }
        else
        {
            if(v==1)
            utility+=1;
            else
            utility+=v*2;    
            v=0;
        }
    }
    for(int i=0;i<10-std::abs(x1-y1);i++)
    {
        if(x1>=y1)
        {
            if(mapping[i][x1-y1+i]=="M") 
            {
                h++;
            }
            else
            {
                if(h==1)
                utility+=1;
                else
                utility+=h*2;    
                h=0;
            }
        }
        else
        {
            if(mapping[y1-x1+i][i]=="M") 
            {
                v++;
            }
            else
            {
                if(v==1)
                utility+=1;
                else
                utility+=v*2;    
                v=0;
            }
        }
    }
    return utility;
}

float Board::find_utility(vector<Cart> ct, vector<string> m, float prev_utility){
	float util;
    if(m.size()==1)
    {
        if(ringsMy<=4)
        {
            util=prev_utility+(5-std::abs(ct[0].x-5))+(5-std::abs(ct[0].y-5));
        }
        else
        {
            util=prev_utility+(std::abs(ct[0].x-5))+(std::abs(ct[0].y-5));    
        }
    }
    else if(m.size()>=2)
    {
        util+=utility_check_row(ct[0].x,ct[0].y,ct[1].x,ct[1].y);
        util+=utility_check_row_all_points(ct[0].x,ct[0].y,ct[1].x,ct[1].y);    
    }



	return util;
}

Tup3 Board::check_row_vertical( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    Tup3 t;
    for(int i=0;i<=10;i++)
    {
        if(mapping[i][x1]=="M") 
            {
                v++;vip=1;
                if(v==5)
                {
                    Cart c1;c1.x=x1;c1.y=i;Cart c2;c2.x=x1;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                    }
                }
            }
        else{v=0;vip=0;}
    }
    return t;
}
Tup3 Board::check_row_horizontal( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    Tup3 t;
    for(int i=0;i<=10;i++)
    {
        if(mapping[y1][i]=="M") 
            {
                h++;hip=1;
                if(h==5)
                {
                    Cart c1;c1.x=x1;c1.y=i;Cart c2;c2.x=x1;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                    }
                }
            }
        else{h=0;hip=0;}
    }
    return t;
}
Tup3 Board::check_row_diagonal( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    Tup3 t;
    for(int i=0;i<10-std::abs(x1-y1);i++)
        {
            if(x1>=y1)
            {
                if(mapping[i][x1-y1+i]=="M") 
                {
                    h++;hip=1;
                    if(h==5)
                    {
                        Cart c1;c1.x=x1-y1+i;c1.y=i;Cart c2;c2.x=x1-y1+i-5;c2.y=i-5;
                        // for (auto i = rings.begin(); i != rings.end(); ++i)
                        for (int i=0; i<RingPos.size(); i++)
                        {
                            t.moves.push_back("RS");
                            t.moves.push_back("RE");
                            t.carts.push_back(c1);
                            t.carts.push_back(c2);
                            //map=removeRow(c1,c2);//------------------------------Make this--------------------------------------
                            //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                            t.moves.push_back("X");
                            t.carts.push_back(RingPos[i]);
                        }
                    }
                }
                else{h=0;hip=0;}
            }
            else
            {
                if(mapping[y1-x1+i][i]=="M") 
                {
                    h++;hip=1;
                    if(h==5)
                    {
                        Cart c1;c1.x=i;c1.y=y1-x1+i;Cart c2;c2.x=i-5;c2.y=y1-x1+i-5;
                        // for (auto i = rings.begin(); i != rings.end(); ++i)
                        for (int i=0; i<RingPos.size(); i++)
                        {
                            t.moves.push_back("RS");
                            t.moves.push_back("RE");
                            t.carts.push_back(c1);
                            t.carts.push_back(c2);
                            //map=removeRow(c1,c2);//------------------------------Make this--------------------------------------
                            //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                            t.moves.push_back("X");
                            t.carts.push_back(RingPos[i]);
                        }
                    }
                }
                else{h=0;hip=0;}
            }
        }
    return t;
}
Tup3 Board::check_row_all_points( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    Tup3 non_intersecting_rows;
    if(x1==x2)
    {
        Tup3 temp1=check_row_horizontal(x1,y1,x2,y2);
        Tup3 temp2=check_row_diagonal(x1,y1,x2,y2);
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp1.moves.begin(),temp1.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp1.carts.begin(),temp1.carts.end());
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp2.moves.begin(),temp2.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp2.carts.begin(),temp2.carts.end());
    }
    else if(y1==y2)
    {
        Tup3 temp1=check_row_vertical(x1,y1,x2,y2);
        Tup3 temp2=check_row_diagonal(x1,y1,x2,y2);
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp1.moves.begin(),temp1.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp1.carts.begin(),temp1.carts.end());
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp2.moves.begin(),temp2.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp2.carts.begin(),temp2.carts.end());
    }
    else
    {
        Tup3 temp1=check_row_vertical(x1,y1,x2,y2);
        Tup3 temp2=check_row_horizontal(x1,y1,x2,y2);
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp1.moves.begin(),temp1.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp1.carts.begin(),temp1.carts.end());
        
        non_intersecting_rows.moves.insert(non_intersecting_rows.moves.end(),temp2.moves.begin(),temp2.moves.end());
        non_intersecting_rows.carts.insert(non_intersecting_rows.carts.end(),temp2.carts.begin(),temp2.carts.end());   
    }
    return non_intersecting_rows;    
}
vector<Tup3> Board::check_row( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    vector<Tup3> output;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    for(int i=0;i<=10;i++)
    {
        if(mapping[y1][i]=="M") 
            {
                h++;hip=1;
                if(h==5)
                {
                    Cart c1;c1.x=x1;c1.y=i;Cart c2;c2.x=x1;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                        output.push_back(t);
                    }
                }
            }
        else{h=0;hip=0;}
        if(mapping[i][x1]=="M") 
            {
                v++;vip=1;
                if(v==5)
                {
                    Cart c1;c1.x=x1;c1.y=i;Cart c2;c2.x=x1;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
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
            if(mapping[i][x1-y1+i]=="M") 
            {
                h++;hip=1;
                if(h==5)
                {
                    Cart c1;c1.x=x1-y1+i;c1.y=i;Cart c2;c2.x=x1-y1+i-5;c2.y=i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                        output.push_back(t);
                    }
                }
            }
            else{h=0;hip=0;}
        }
        else
        {
            if(mapping[y1-x1+i][i]=="M") 
            {
                h++;hip=1;
                if(h==5)
                {
                    Cart c1;c1.x=i;c1.y=y1-x1+i;Cart c2;c2.x=i-5;c2.y=y1-x1+i-5;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        //map=removeRow(c1,c2);//------------------------------Make this--------------------------------------
                        //Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                        output.push_back(t);
                    }
                }
            }
            else{h=0;hip=0;}
        }
    }
    return output;
}

vector<MoveVal> Board::find_neighbours(/*Cart opp_c_in, Cart opp_c_fin,*/ Cart c, int dir, bool my_turn)//c--> position of ring to be moved
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

    int t=0; //t=1--> a marker has been encountered
    
    Children ch;


    //------------------------------------Checkin rows made by opponent----------------------------------------------------            
           /* 
            Tup3 non_intersecting_rows_by_opp = check_row_all_points(opp_c_in.x,opp_c_in.y,opp_c_fin.x,opp_c_fin.y);
            m.insert(m.end(),non_intersecting_rows_by_opp.moves.begin(),non_intersecting_rows_by_opp.moves.end());
            ct.insert(ct.end(),non_intersecting_rows_by_opp.carts.begin(),non_intersecting_rows_by_opp.carts.end());           
            vector<Tup3> intersecting_rows_by_opp = check_row(opp_c_in.x,opp_c_in.y,opp_c_fin.x,opp_c_fin.y);
            
            if(t_vec.size() > 0)
            {
                for(int j=0;j<t_vec.size();j++)
                {
                    m.insert(m.end(),intersecting_rows_by_opp.moves.begin(),intersecting_rows_by_opp.moves.end());
                    ct.insert(ct.end(),intersecting_rows_by_opp.carts.begin(),intersecting_rows_by_opp.carts.end());
                    undo_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);

                }
            }    
*/
    //------------------------------------Checkin rows made by opponent----------------------------------------------------

    cout << "BEGINNING WHILE" << endl;

    MoveVal mvl;
    while(!(mapping[y][x]=="R" || mapping[y][x]=="RO" ||mapping[y][x]=="I"))
    {
        cout << "NEW " << endl;
         
        if(mapping[y][x]=="E" && t==0)
        {
            cout << "IF" << endl;
            vector<string> m;
            vector<Cart> ct;

            Cart r;
            r.x=x;
            r.y=y;
            m.push_back("S");
            m.push_back("M");
            ct.push_back(c);
            ct.push_back(r);
            prev_utility = 0;/////*****************************************************************************************

            execute_move_sequence(ct,m,my_turn);
            cout << "Initial Move Executed" << endl;
            Tup3 non_intersecting_rows = check_row_all_points(c.x,c.y,x,y);
            cout << "non_intersecting_rows" << endl;
            m.insert(m.end(),non_intersecting_rows.moves.begin(),non_intersecting_rows.moves.end());
            ct.insert(ct.end(),non_intersecting_rows.carts.begin(),non_intersecting_rows.carts.end());
            execute_move_sequence(non_intersecting_rows.carts, non_intersecting_rows.moves, my_turn);            
            

            vector<Tup3> t_vec = check_row(c.x,c.y,x,y);
            cout << "Before if" << endl;
            if(t_vec.size() > 0)
            {
                cout << "Size > 0" << endl;
                for(int j=0;j<t_vec.size();j++)
                {
                    m.insert(m.end(),t_vec[j].moves.begin(),t_vec[j].moves.end());
                    ct.insert(ct.end(),t_vec[j].carts.begin(),t_vec[j].carts.end());          
                    mvl.movetype = m;
                    mvl.cart_xy = ct;

             		execute_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);
                    mvl.utility=find_utility(ct, m, prev_utility);//------------------------------------Make this-----------------------------------------
                    cout << "UTILITYYY" << endl;
                    ch.neighbours.push_back(mvl);
                    cout << "BEFORE POPPING" << endl;
                    m.pop_back();m.pop_back();m.pop_back();
                    ct.pop_back();ct.pop_back();ct.pop_back();
                    cout << "AFTER POPPING" << endl;
                    undo_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);

                }
            }
            
            else
            {
                cout << "size = 0" << endl;
	            mvl.movetype = m;
	            mvl.cart_xy = ct;
	            mvl.utility=find_utility(ct, m, prev_utility);//------------------------------------Make this-----------------------------------------
	            ch.neighbours.push_back(mvl);
	        }
	        undo_move_sequence(ct,m, my_turn);
            cout << "UNDOO" << endl;
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
            cout << "UNDOO" << endl;

        }
        else if(mapping[y][x]=="M" || mapping[y][x]=="MO")
        {
            cout << "ELSE IF" << endl;
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
            cout << "Break wala else if" << endl;
            vector<string> m;
            vector<Cart> ct;
            Cart r;
            r.x=x;r.y=y;
            m.push_back("S");
            m.push_back("M");
            ct.push_back(c);
            ct.push_back(r);
            prev_utility = 0;

            execute_move_sequence(ct,m, my_turn);
            Tup3 non_intersecting_rows = check_row_all_points(c.x,c.y,x,y);
            m.insert(m.end(),non_intersecting_rows.moves.begin(),non_intersecting_rows.moves.end());
            ct.insert(ct.end(),non_intersecting_rows.carts.begin(),non_intersecting_rows.carts.end());
            execute_move_sequence(non_intersecting_rows.carts, non_intersecting_rows.moves, my_turn);
            

            vector<Tup3> t_vec = check_row(c.x,c.y,x,y);
            
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
        if (!(x<0 || y<0 || x>10 || y>10)){
            break;
        }
    }
    cout << "Returning neighbours" << endl;
    return ch.neighbours;
}

vector<MoveVal> Board::moveRing(bool my_turn)
{


    vector<MoveVal> padosi;
    for (int i=0; i < RingPos.size(); i++) 
    {
        for(int j=1;j<=6;j++)
        {
            vector<MoveVal> p1= find_neighbours(RingPos[i],j, my_turn);
            padosi.insert(padosi.end(),p1.begin(),p1.end());
            cout << i << ", " << j << endl;
        }
    }
    return padosi; 
}


vector<MoveVal> Board::placeRing(bool my_turn){
   cout << "Place Ring Called" <<endl;
  /**/ 
   float prev_utility;
   vector<MoveVal> all_possible_moves;
   if(RingPos.size()<=4)
   {
       for(int x=4;x<=6;x++)
       {
           for(int y=4;y<=6;y++)
           {   
               MoveVal move;
               if(mapping[y][x]=="E")
               {
                   Cart c;
                   c.x=x;
                   c.y=y;
                   move.movetype.push_back("P");
                   move.cart_xy.push_back(c);
                   prev_utility = utility_board;//*************************************Do This ********************************************************
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
               MoveVal move; 
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
               MoveVal move; 
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
        cout << "MOVE RING CALLED" << endl;
        vector<MoveVal> p=moveRing(my_turn);
        cout << "Vector of Move Val Returned" << endl;
        children.neighbours = p;
        children.next_state = 2;

    }
    // if(playerstate==3)
    // {
    // }
}

