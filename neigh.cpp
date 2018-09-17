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

float Board::find_utility(){
    float utils= 0;
    utils += ringsMy*10;
    utils -= ringsOpp*10;
    utils += markersMy;
    utils -= markersOpp;
    return utils;

}


//     else if(m.size()>=2)
//     {
//         util+=utility_check_row(ct[0].x,ct[0].y,ct[1].x,ct[1].y);
//         util+=utility_check_row_all_points(ct[0].x,ct[0].y,ct[1].x,ct[1].y);    
//     }


vector<Tup3> Board::check_row_vertical( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    vector<Tup3> output;
    for(int i=0;i<=10;i++)
    {
        if(mapping[i][x1]=="M") 
            {
                v++;
                if(v==5)
                {
                    Cart c1;c1.x=x1;c1.y=i-4;Cart c2;c2.x=x1;c2.y=i;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                        output.push_back(t);
                    }
                }
            }
        else{v=0;}
    }
    return output;
}
vector<Tup3> Board::check_row_horizontal( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    vector<Tup3> output;
    for(int i=0;i<=10;i++)
    {
        if(mapping[y1][i]=="M") 
            {
                h++;
                if(h==5)
                {
                    Cart c1;c1.x=i-4;c1.y=y1;Cart c2;c2.x=i;c2.y=y1;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPos.size(); i++)
                    {
                        
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPos[i]);
                        output.push_back(t);
                    }
                }
            }
        else{h=0;}
    }
    return output;
}
vector<Tup3> Board::check_row_diagonal( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    vector<Tup3> output;
    for(int i=0;i<10-std::abs(x1-y1);i++)
        {
            if(x1>=y1)
            {
                if(mapping[i][x1-y1+i]=="M") 
                {
                    h++;;
                    if(h==5)
                    {
                        
                        Cart c1;c1.x=x1-y1+i-4;c1.y=i-4;Cart c2;c2.x=x1-y1+i;c2.y=i;
                        // for (auto i = rings.begin(); i != rings.end(); ++i)
                        for (int i=0; i<RingPos.size(); i++)
                        {
                            Tup3 t;
                            t.moves.push_back("RS");
                            t.moves.push_back("RE");
                            t.carts.push_back(c1);
                            t.carts.push_back(c2);
                            t.moves.push_back("X");
                            t.carts.push_back(RingPos[i]);
                            output.push_back(t);
                        }
                    }
                }
                else{h=0;}
            }
            else
            {
                if(mapping[y1-x1+i][i]=="M") 
                {
                    h++;
                    if(h==5)
                    {
                        Cart c1;c1.x=i-4;c1.y=y1-x1+i-4;Cart c2;c2.x=i;c2.y=y1-x1+i;
                        // for (auto i = rings.begin(); i != rings.end(); ++i)
                        for (int i=0; i<RingPos.size(); i++)
                        {
                            Tup3 t;
                            t.moves.push_back("RS");
                            t.moves.push_back("RE");
                            t.carts.push_back(c1);
                            t.carts.push_back(c2);
                            t.moves.push_back("X");
                            t.carts.push_back(RingPos[i]);
                            output.push_back(t);
                        }
                    }
                }
                else{h=0;}
            }
        }
    return output;
}
vector<Tup3> Board::check_row_all_points( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    vector<Tup3> non_intersecting_rows;
    if(x1==x2)
    {
        vector<Tup3> temp1=check_row_horizontal(x1,y1,x2,y2);
        vector<Tup3> temp2=check_row_diagonal(x1,y1,x2,y2);
        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());
    }
    else if(y1==y2)
    {
        vector<Tup3> temp1=check_row_vertical(x1,y1,x2,y2);
        vector<Tup3> temp2=check_row_diagonal(x1,y1,x2,y2);
        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());
    }
    else
    {
        vector<Tup3> temp1=check_row_vertical(x1,y1,x2,y2);
        vector<Tup3> temp2=check_row_horizontal(x1,y1,x2,y2);

        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());   
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

int Board::check_if_row(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y)
{
    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int check=0;
    if(x1==x2)
    {
        for(int i=y1;i<=y2;i++)
        {
            if(mapping[i][x1]!="M")
            {
                check=1;break;
            }
        }
    }
    else if(y1==y2)
    {
        for(int i=x1;i<=x2;i++)
        {
            if(mapping[y1][i]!="M")
            {
                check=1;break;
            }
        }
    }
    else
    {
        if(x1<x2)
        {
            while(x1<x2 && y1<y2)
            {
                if(mapping[y1][x1]!="M")
                {
                    check=1;break;
                }
                x1++;y1++;        
            }
        }
        if(x1>x2)
        {
            while(x1>x2 && y1>y2)
            {
                if(mapping[y1][x1]!="M")
                {
                    check=1;break;
                }
                x1--;y1--;        
            }
        }
    }
    return check;
}

vector<MoveVal> Board::find_neighbours(/*Cart opp_c_in, Cart opp_c_fin,*/ Cart c, int dir, bool my_turn)//c--> position of ring to be moved
{   
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
    if ((x<0 || y<0 || x>10 || y>10)){
    
        cerr << "Returning neighbours" << endl;
        return ch.neighbours;
    }


    //------------------------------------Checkin rows made by opponent----------------------------------------------------            
            
            // vector<Tup3> non_intersecting_rows_by_opp = check_row_all_points(opp_c_in.x,opp_c_in.y,opp_c_fin.x,opp_c_fin.y);
            


            // for(int i=0;i<non_intersecting_rows_by_opp.size();i++)
            // {
            //     for(int j=i+1;j<non_intersecting_rows_by_opp.size();j++)
            //     {
            //         if(check_if_row(non_intersecting_rows_by_opp[j].carts[0].x,non_intersecting_rows_by_opp[j].carts[0].y,non_intersecting_rows_by_opp[j].carts[1].x,non_intersecting_rows_by_opp[j].carts[1].y,))
            //         {
            //             m.push_back("RS");
            //             m.push_back("RE");
            //             m.push_back("X");
            //             ct.push_back(non_intersecting_rows_by_opp[j].carts[0]);
            //             ct.push_back(non_intersecting_rows_by_opp[j].carts[1]);
            //             ct.push_back(non_intersecting_rows_by_opp[j].carts[2]);
            //         }                       
            //     }










            // m.insert(m.end(),non_intersecting_rows_by_opp.moves.begin(),non_intersecting_rows_by_opp.moves.end());
            // ct.insert(ct.end(),non_intersecting_rows_by_opp.carts.begin(),non_intersecting_rows_by_opp.carts.end());           
            // vector<Tup3> intersecting_rows_by_opp = check_row(opp_c_in.x,opp_c_in.y,opp_c_fin.x,opp_c_fin.y);
            
            // if(t_vec.size() > 0)
            // {
            //     for(int j=0;j<t_vec.size();j++)
            //     {
            //         m.insert(m.end(),intersecting_rows_by_opp.moves.begin(),intersecting_rows_by_opp.moves.end());
            //         ct.insert(ct.end(),intersecting_rows_by_opp.carts.begin(),intersecting_rows_by_opp.carts.end());
            //         undo_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);

            //     }
            // }    

    //------------------------------------Checkin rows made by opponent----------------------------------------------------

    cerr << "BEGINNING WHILE" << endl;
    cerr << mapping[y][x] << " t " << t << endl;

    MoveVal mvl;
    while(!(mapping[y][x]=="R" || mapping[y][x]=="RO" ||mapping[y][x]=="I"))
    {
        cerr << "NEW ";
        cerr << mapping[y][x] << " t " << t << endl;
         
        if(mapping[y][x]=="E" && t==0)
        {
            cerr << "IF" << endl;
            vector<string> m;
            vector<Cart> ct;

            vector<string> m_temp;
            vector<Cart> ct_temp;
            
            Cart r;
            r.x=x;
            r.y=y;
            m.push_back("S");
            m.push_back("M");
            ct.push_back(c);
            ct.push_back(r);

            m_temp.push_back("S");
            m_temp.push_back("M");
            ct_temp.push_back(c);
            ct_temp.push_back(r);

            execute_move_sequence(ct,m,my_turn);
            cerr << "Initial Move Executed" << endl;
            vector<Tup3> t_vec;
            if(x==c.x)
            {
                t_vec = check_row_horizontal(c.x,c.y,x,y);
            }
            else if(y==c.y)
            {
                t_vec = check_row_vertical(c.x,c.y,x,y);
            }
            else
            {
                t_vec = check_row_diagonal(c.x,c.y,x,y);
            }


            vector<Tup3> non_intersecting_rows = check_row_all_points(c.x,c.y,x,y);
            non_intersecting_rows.insert(non_intersecting_rows.end(),t_vec.begin(),t_vec.end());
            cerr << "non_intersecting_rows" << endl;
            if(non_intersecting_rows.size() > 0)
                {
                    vector<string> m_temp_1;
                    vector<Cart> ct_temp_1;
                    for(int i=0;i<non_intersecting_rows.size();i++)
                    {
                        for(int j=i+1;j<non_intersecting_rows.size();j++)
                        {
                            if(check_if_row(non_intersecting_rows[j].carts[0].x,non_intersecting_rows[j].carts[0].y,non_intersecting_rows[j].carts[1].x,non_intersecting_rows[j].carts[1].y)==0)
                            {
                                m.push_back("RS");
                                m.push_back("RE");
                                m.push_back("X");
                                ct.push_back(non_intersecting_rows[j].carts[0]);
                                ct.push_back(non_intersecting_rows[j].carts[1]);
                                ct.push_back(non_intersecting_rows[j].carts[2]);

                                m_temp_1.push_back("RS");
                                m_temp_1.push_back("RE");
                                m_temp_1.push_back("X");
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[0]);
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[1]);
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[2]);
                                if(myturn)
                                {
                                    if((m_temp_1.size()/3)>(3-ringsMy)) break;
                                }
                                else
                                {
                                    if((m_temp_1.size()/3)>(3-ringsOpp)) break;   
                                }
                            }                       
                        }
                        execute_move_sequence(ct_temp_1, m_temp_1, my_turn);

         
                        mvl.movetype = m;
                        mvl.cart_xy = ct;

                        // execute_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);
                            // cerr << "UTILITYYY" << endl;
                        ch.neighbours.push_back(mvl);
                            // cerr << "BEFORE POPPING" << endl;
                        // m.pop_back();m.pop_back();m.pop_back();
                        // ct.pop_back();ct.pop_back();ct.pop_back();
                            // cerr << "AFTER POPPING" << endl;
                        undo_move_sequence( ct_temp_1,m_temp_1, my_turn);

                    }
                }
                
                else
                {
                    cerr << "size = 0" << endl;
                    mvl.movetype = m;
                    mvl.cart_xy = ct;
                    ch.neighbours.push_back(mvl);
                }
                undo_move_sequence(ct_temp,m_temp, my_turn);

                
            cerr << "UNDOO" << endl;
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
            cerr << "UNDOO" << endl;

        }
        else if(mapping[y][x]=="M" || mapping[y][x]=="MO")
        {
            cerr << "ELSE IF" << endl;
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
            cerr << "Break wala else if" << endl;
            cerr << "IF" << endl;
            vector<string> m;
            vector<Cart> ct;

            vector<string> m_temp;
            vector<Cart> ct_temp;
            
            Cart r;
            r.x=x;
            r.y=y;
            m.push_back("S");
            m.push_back("M");
            ct.push_back(c);
            ct.push_back(r);

            m_temp.push_back("S");
            m_temp.push_back("M");
            ct_temp.push_back(c);
            ct_temp.push_back(r);

            execute_move_sequence(ct,m,my_turn);
            cerr << "Initial Move Executed" << endl;
            vector<Tup3> t_vec;
            if(x==c.x)
            {
                t_vec = check_row_horizontal(c.x,c.y,x,y);
            }
            else if(y==c.y)
            {
                t_vec = check_row_vertical(c.x,c.y,x,y);
            }
            else
            {
                t_vec = check_row_diagonal(c.x,c.y,x,y);
            }


            vector<Tup3> non_intersecting_rows = check_row_all_points(c.x,c.y,x,y);
            non_intersecting_rows.insert(non_intersecting_rows.end(),t_vec.begin(),t_vec.end());
            cerr << "non_intersecting_rows" << endl;
            if(non_intersecting_rows.size() > 0)
                {
                    vector<string> m_temp_1;
                    vector<Cart> ct_temp_1;
                    for(int i=0;i<non_intersecting_rows.size();i++)
                    {
                        for(int j=i+1;j<non_intersecting_rows.size();j++)
                        {
                            if(check_if_row(non_intersecting_rows[j].carts[0].x,non_intersecting_rows[j].carts[0].y,non_intersecting_rows[j].carts[1].x,non_intersecting_rows[j].carts[1].y)==0)
                            {
                                m.push_back("RS");
                                m.push_back("RE");
                                m.push_back("X");
                                ct.push_back(non_intersecting_rows[j].carts[0]);
                                ct.push_back(non_intersecting_rows[j].carts[1]);
                                ct.push_back(non_intersecting_rows[j].carts[2]);

                                m_temp_1.push_back("RS");
                                m_temp_1.push_back("RE");
                                m_temp_1.push_back("X");
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[0]);
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[1]);
                                ct_temp_1.push_back(non_intersecting_rows[j].carts[2]);
                            }                       
                        }
                        execute_move_sequence(ct_temp_1, m_temp_1, my_turn);

         
                        mvl.movetype = m;
                        mvl.cart_xy = ct;

                        // execute_move_sequence(t_vec[j].carts, t_vec[j].moves, my_turn);
                            // cerr << "UTILITYYY" << endl;
                        ch.neighbours.push_back(mvl);
                            // cerr << "BEFORE POPPING" << endl;
                        // m.pop_back();m.pop_back();m.pop_back();
                        // ct.pop_back();ct.pop_back();ct.pop_back();
                            // cerr << "AFTER POPPING" << endl;
                        undo_move_sequence( ct_temp_1,m_temp_1, my_turn);

                    }
                }
                
                else
                {
                    cerr << "size = 0" << endl;
                    mvl.movetype = m;
                    mvl.cart_xy = ct;
                    ch.neighbours.push_back(mvl);
                }
                undo_move_sequence(ct_temp,m_temp, my_turn);
            break;  
        }
        cerr << x << ", " << y << endl;
        if ((x<0 || y<0 || x>10 || y>10)){
            break;
        }
    }
    cerr << "Returning neighbours" << endl;
    return ch.neighbours;
}

vector<MoveVal> Board::moveRing(bool my_turn)
{


    vector<MoveVal> padosi;
    for (int i=0; i < RingPos.size(); i++) 
    {
        for(int j=1;j<=6;j++)
        {
            cerr << "Next Dir" << i << ", " << j << endl;
            // printConfig();
            cerr <<"RingPos" << RingPos[i].x << ", " << RingPos[i].y << endl;
            vector<MoveVal> p1= find_neighbours(RingPos[i],j, my_turn);
            padosi.insert(padosi.end(),p1.begin(),p1.end());

        }
    }
    return padosi; 
}


vector<MoveVal> Board::placeRing(bool my_turn){
   cerr << "Place Ring Called" <<endl;
  /**/ 
   vector<MoveVal> all_possible_moves;
   cerr << " RINGS POS SIZE **************************** " << RingPos.size() << endl;
   int rings_temp = RingPos.size();
   if(rings_temp==0 || rings_temp==1 || rings_temp==3|| rings_temp==4)
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
                   execute_move_sequence(move.cart_xy, move.movetype, my_turn);
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
               execute_move_sequence(move.cart_xy, move.movetype, my_turn);
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
               execute_move_sequence(move.cart_xy, move.movetype, my_turn);
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
        // if(RingPos.size()==5) playerstate=2;//------------------------------------------check syntax------------------------------
        children.neighbours = move;
        children.next_state = 1;

    }
    if(playerstate==2)
    {   
        cerr << "MOVE RING CALLED" << endl;
        vector<MoveVal> p=moveRing(my_turn);
        cerr << "Vector of Move Val Returned" << endl;
        children.neighbours = p;
        children.next_state = 2;

    }
    // if(playerstate==3)
    // {
    // }
}

    