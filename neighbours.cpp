#include "board.h"    

float Board::all_utlity()
{
    int two,three,four,two_opp,three_opp,four_opp;int h=0;int v=0;int h_opp=0;int v_opp=0;
    two=three=four=two_opp=three_opp=four_opp=0;
    for(int i=0;i<=2*board_size;i++)
    {
        for(int j=0;j<=2*board_size;j++)
        {
            if(mapping[j][i]=="M")
            {
                h++;
            }
            else
            {
                if(h==2) two++;
                if(h==3) three++;
                if(h==4) four++;
                // if(seq_length == 6 && h==5) five++;
                h=0;
            }
            if(mapping[j][i]=="MO")
            {
                h_opp++;
            }
            else
            {
                if(h_opp==2) two_opp++;
                if(h_opp==3) three_opp++;
                if(h_opp==4) four_opp++;
                h_opp=0;
            }
            if(mapping[i][j]=="M")
            {
                v++;
            }
            else
            {
                if(v==2) two++;
                if(v==3) three++;
                if(v==4) four++;
                v=0;
            }
            if(mapping[i][j]=="MO")
            {
                v_opp++;
            }
            else
            {
                if(v_opp==2) two_opp++;
                if(v_opp==3) three_opp++;
                if(v_opp==4) four_opp++;
                v_opp=0;
            }

        }
    }
    v=0;v_opp=0;
  for(int delta =-5;delta<=5;delta++)
    {
        int x,y;
        for(int i=std::max(0,-delta) ; i<=10; i++)
           {
               y = i;
               x = i + delta;
               if (x >10 ||y >10 || x<0 || y<0){
                   break;
               }
               if(mapping[y][x]=="M")
               {
                   v++;
               }
               else
                {
                    if(v==2) two++;
                    if(v==3) three++;
                    if(v==4) four++;
                    v=0;
                }
                if(mapping[y][x]=="MO")
               {
                   v_opp++;
               }
               else
                {
                    if(v_opp==2) two_opp++;
                    if(v_opp==3) three_opp++;
                    if(v_opp==4) four_opp++;
                    v_opp=0;
                }
           }
      }
      return std::pow(2,two)+std::pow(2,three)+std::pow(2,four) -std::pow(2,two_opp)-std::pow(2,three_opp)-std::pow(2,four_opp);

}

float Board::edge_utility(){
    int edge1 = 0;
    int edge2 = 0;
    int  edge3 = 0;
    int  edge4 = 0;
    int  edge5 = 0;
    int edge6  = 0;
    for (int i=1;i<=4;i++)
    {
        if(mapping[i][0]=="M" || mapping[i][0]=="R")
        {
            edge1++;
        }
        if(mapping[0][i]=="M" || mapping[0][i]=="R")
        {
            edge2++;
        }
        if(mapping[i+5][10]=="M" || mapping[i+5][10]=="R")
        {
            edge3++;
        }
        if(mapping[10][i+5]=="M" || mapping[10][i+5]=="R")
        {
            edge4++;
        }
        if(mapping[i+5][i]=="M" || mapping[i+5][i]=="R")
        {
            edge5++;
        }
        if(mapping[i][i+5]=="M" || mapping[i][i+5]=="R")
        {
            edge6++;
        }
        
    }
    return pow(edge1 - 1,4) + pow(edge2 - 1,4) + pow(edge3 - 1,4) + pow(edge4-1, 4) + pow(edge5 - 1, 4) + pow(edge6 - 1, 4);


}
float Board::rings_utility(){
    int counter=0;
    for (int i=0;i<RingPos.size(); i++){
        int x1 = RingPos[i].x;
        int y1 = RingPos[i].y;
        if (x1 < 10 && mapping[y1][x1+1] == "M"){
            counter ++;
        }
        if (y1 < 10 && mapping[y1+1][x1] == "M"){
            counter ++;
        }
        if (x1 > 0 && mapping[y1][x1-1] == "M"){
            counter ++;
        }
        if (y1 > 0 && mapping[y1-1][x1] == "M"){
            counter ++;
        }
        if (x1 < 10 && y1 < 10 && mapping[y1+1][x1+1] == "M"){
            counter ++;
        }
        if (x1 > 0 && y1 > 0 && mapping[y1-1][x1-1] == "M"){
            counter ++;
        }
    }
    int counter_opp = 0;
    for (int i=0;i<RingPosOpp.size(); i++){
        int x1 = RingPosOpp[i].x;
        int y1 = RingPosOpp[i].y;
        if (x1 < 10 && mapping[y1][x1+1] == "MO"){
            counter_opp ++;
        }
        if (y1 < 10 && mapping[y1+1][x1] == "MO"){
            counter_opp ++;
        }
        if (x1 > 0 && mapping[y1][x1-1] == "MO"){
            counter_opp ++;
        }
        if (y1 > 0 && mapping[y1-1][x1] == "MO"){
            counter_opp ++;
        }
        if (x1 < 10 && y1 < 10 && mapping[y1+1][x1+1] == "MO"){
            counter_opp ++;
        }
        if (x1 > 0 && y1 > 0 && mapping[y1-1][x1-1] == "MO"){
            counter_opp ++;
        }
    }
    float util = (counter-counter_opp) *2;
    return util;
}
float Board::find_utility(){
    float utils = 0;
    // if (RingPos.size() >= 2){
    //    utils += std::pow(10,( 5 -RingPos.size() )*2);
    //    utils -= std::pow(10,( 5 -RingPosOpp.size())*3); 
    // }
    // else{
       // cerr << "ERORORRORRROROR***************************" << endl;
    //     utils -= std::pow(10,( 3)*3);
    //     utils += std::pow(10,( 3)*2);
    // }
   
    int delta_markers = markersMy - markersOpp;
    // int delta_rings = RingPos.size() - RingPosOpp.size();
    // utils += markersMy * (std::pow(10,delta_rings))/100;
    vector<float> balance; 
    vector<float> balance_opp; 
    if(seq_length == 5)
    {
        balance= {200,200, 200, 70, 20, 0};
        balance_opp = {300,300, 300, 100, 50, 0};
    }
    else if(seq_length == 6)
    {
        balance = {200, 200, 200, 200, 70, 20, 0};
        balance_opp = {300, 300, 300, 300, 100, 50, 0};
    }
    else
    {
        cerr << "Wrong seq_length"<<endl;
    }
    utils += balance[RingPos.size()];
    utils -= balance[RingPosOpp.size()];
    // utils -= (RingPos.size() - RingPosOpp.size())*10000;
    utils += markersMy;
    utils -= markersOpp;
    // utils += (float)delta_markers;
    // utils += rings_utility();
    // utils+=all_utlity();
    // utils-=all_utlity_opp();
    // utils-= 2* edge_utility();
    // cerr << "CALCULATING UTILITY: markersMy = " << markersMy <<", MarkersOpp = " <<markersOpp << ", RingsMyScore = " <<  balance[RingPos.size()] << ", RingsOppScore = "<< balance[RingPosOpp.size()] << endl;
    // cerr << "UTILITY = "<< utils << endl;
    return utils;

}


vector<Tup3> Board::check_row_vertical_my( int init_pos_x,int init_pos_y,bool my_turn )
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_vertical_my\n";

    // cerr <<"Checkin Row Vert: x= " << init_pos_x << " y: " << init_pos_y << endl;
    int x1=init_pos_x;int y1=init_pos_y;
    string marker_check;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    if(my_turn) marker_check="M";
    else marker_check="MO";
    vector<Tup3> output;
    for(int i=0;i<=2*board_size;i++)
    {
        if(mapping[i][x1]==marker_check) 
            {
                v++;
                if(v==seq_length)
                {

                    Cart c1;c1.x=x1;c1.y=i-(seq_length-1);Cart c2;c2.x=x1;c2.y=i;
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
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below check_row_vertical_my\n";

}
vector<Tup3> Board::check_row_vertical_opp( int init_pos_x,int init_pos_y,bool my_turn )
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_vertical_opp\n";

    // cerr <<"Checkin Row Vert: x= " << init_pos_x << " y: " << init_pos_y << endl;
    int x1=init_pos_x;int y1=init_pos_y;
    string marker_check;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    if(my_turn) marker_check="M";
    else marker_check="MO";
    vector<Tup3> output;
    for(int i=0;i<=2*board_size;i++)
    {
        if(mapping[i][x1]==marker_check) 
            {
                v++;
                if(v==(seq_length))
                {

                    Cart c1;c1.x=x1;c1.y=i-(seq_length-1);Cart c2;c2.x=x1;c2.y=i;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPosOpp.size(); i++)
                    {
                        
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPosOpp[i]);
                        output.push_back(t);
                    }
                }
            }
        else{v=0;}
    }
    return output;
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below check_row_vertical_opp\n";

}

vector<Tup3> Board::check_row_vertical( int init_pos_x,int init_pos_y ,bool my_turn)
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_vertical\n";

    if (my_turn) return check_row_vertical_my(init_pos_x, init_pos_y, my_turn);
    else return check_row_vertical_opp(init_pos_x, init_pos_y, my_turn);
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " b check_row_vertical\n";

}

vector<Tup3> Board::check_row_horizontal_my( int init_pos_x,int init_pos_y,bool my_turn )
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_horizontal_my\n";

    int x1=init_pos_x;int y1=init_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    vector<Tup3> output;
    string marker_check;
    if(my_turn) marker_check="M";
    else marker_check="MO";
    for(int i=0;i<=2*board_size;i++)
    {
        if(mapping[y1][i]==marker_check) 
            {
                h++;
                if(h==seq_length)
                {
                    Cart c1;c1.x=i-(seq_length-1);c1.y=y1;Cart c2;c2.x=i;c2.y=y1;
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
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_horizontal_my\n";

}
vector<Tup3> Board::check_row_horizontal_opp( int init_pos_x,int init_pos_y,bool my_turn )
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_horizontal_opp\n";

    int x1=init_pos_x;int y1=init_pos_y;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    vector<Tup3> output;
    string marker_check;
    if(my_turn) marker_check="M";
    else marker_check="MO";
    for(int i=0;i<=2*board_size;i++)
    {
        if(mapping[y1][i]==marker_check) 
            {
                h++;
                if(h==seq_length)
                {
                    Cart c1;c1.x=i-(seq_length-1);c1.y=y1;Cart c2;c2.x=i;c2.y=y1;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPosOpp.size(); i++)
                    {
                        
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPosOpp[i]);
                        output.push_back(t);
                    }
                }
            }
        else{h=0;}
    }
    return output;
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " b check_row_horizontal_opp\n";

}

vector<Tup3> Board::check_row_horizontal( int init_pos_x,int init_pos_y,bool my_turn )
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_horizontal\n";

    if (my_turn) return  check_row_horizontal_my(init_pos_x, init_pos_y, my_turn);
    else return check_row_horizontal_opp(init_pos_x, init_pos_y, my_turn);
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " b check_row_horizontal\n";

}

vector<Tup3> Board::check_row_diagonal_my( int init_pos_x,int init_pos_y,bool my_turn)
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_diagonal_my\n";

    // cerr << "D " << endl;
    int x1=init_pos_x;int y1=init_pos_y;
    int delta = x1-y1;
    string marker_check;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    if(my_turn) marker_check="M";
    else marker_check="MO";
    vector<Tup3> output;
    int x,y;
    for(int i=std::max(0,-delta) ; i<=2*board_size; i++)
        {
            y = i;
            x = i + delta; 
            if (x >2*board_size ||y >2*board_size || x<0 || y<0){
                break;
            }
            if(mapping[y][x]==marker_check) 
            {
                h++;;
                if(h==seq_length)
                {
                    // cerr << "Diag " << endl;
                    
                    Cart c1;
                    c1.x = x - (seq_length-1);
                    c1.y = y - (seq_length-1);
                    Cart c2;
                    c2.x = x;
                    c2.y = y;
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
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " b check_row_diagonal_my\n";

}
vector<Tup3> Board::check_row_diagonal_opp( int init_pos_x,int init_pos_y,bool my_turn)
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_diag_opp\n";


    // cerr << "D " << endl;
    int x1=init_pos_x;int y1=init_pos_y;
    int delta = x1-y1;
    string marker_check;
    int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
    if(my_turn) marker_check="M";
    else marker_check="MO";
    vector<Tup3> output;
    int x,y;
    for(int i=std::max(0,-delta) ; i<=2*board_size; i++)
        {
            y = i;
            x = i + delta; 
            if (x >2*board_size ||y >2*board_size || x<0 || y<0){
                break;
            }
            if(mapping[y][x]==marker_check) 
            {
                h++;;
                if(h==seq_length)
                {
                    // cerr << "Diag " << endl;
                    
                    Cart c1;
                    c1.x = x - (seq_length-1);
                    c1.y = y - (seq_length-1);
                    Cart c2;
                    c2.x = x;
                    c2.y = y;
                    // for (auto i = rings.begin(); i != rings.end(); ++i)
                    for (int i=0; i<RingPosOpp.size(); i++)
                    {
                        Tup3 t;
                        t.moves.push_back("RS");
                        t.moves.push_back("RE");
                        t.carts.push_back(c1);
                        t.carts.push_back(c2);
                        t.moves.push_back("X");
                        t.carts.push_back(RingPosOpp[i]);
                        output.push_back(t);
                    }
                }
            }
            else{h=0;}
            
        }
    return output;
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " b check_row_diag_opp\n";

}
vector<Tup3> Board::check_row_diagonal( int init_pos_x,int init_pos_y,bool my_turn )
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_diagonal\n";

    if (my_turn) return check_row_diagonal_my(init_pos_x, init_pos_y, my_turn);
    else return check_row_diagonal_opp(init_pos_x, init_pos_y, my_turn);
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " b check_row_diagonal\n";

}
vector<Tup3> Board::check_row_all_points_each( int init_pos_x,int init_pos_y,int check, bool my_turn )
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_all_points_each\n";

    int x1=init_pos_x;int y1=init_pos_y;
    vector<Tup3> non_intersecting_rows;
    if(check==0)
    {
        vector<Tup3> temp1=check_row_horizontal(x1,y1,my_turn);
        vector<Tup3> temp2=check_row_diagonal(x1,y1,my_turn);
        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());
    }
    else if(check==1)
    {
        vector<Tup3> temp1=check_row_vertical(x1,y1,my_turn);
        vector<Tup3> temp2=check_row_diagonal(x1,y1,my_turn);
        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());
    }
    else
    {
        vector<Tup3> temp1=check_row_vertical(x1,y1,my_turn);
        vector<Tup3> temp2=check_row_horizontal(x1,y1,my_turn);

        non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());        
        non_intersecting_rows.insert(non_intersecting_rows.end(),temp2.begin(),temp2.end());   
    }
    return non_intersecting_rows;    
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " b check_row_all_points_each\n";

}

int Board::check_if_row(int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y, int ring_x, int ring_y, bool my_turn)
{
    // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_if_row\n";

    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    int check=0;

    string rings_check = "RO";
    string marker_check = "MO";
    if (my_turn){
        rings_check = "R";
        marker_check = "M";
    }

    if (mapping[ring_y][ring_x] != rings_check){
        return 1;
    }
        if(x1==x2)
    {
        for(int i=y1;i<=y2;i++)
        {
            if(mapping[i][x1]!=marker_check)
            {
                check=1;break;
            }
        }
    }
    else if(y1==y2)
    {
        for(int i=x1;i<=x2;i++)
        {
            if(mapping[y1][i]!=marker_check)
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
                if(mapping[y1][x1]!=marker_check)
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
                if(mapping[y1][x1]!=marker_check)
                {
                    check=1;break;
                }
                x1--;y1--;        
            }
        }
    }
        // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " b check_if_row\n";

    return check;

}

vector<Tup3> Board::check_row_all_points( int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y,bool my_turn )
{
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check_row_all_points\n";

    int x1=init_pos_x;int y1=init_pos_y;
    int x2=final_pos_x;int y2=final_pos_y;
    vector<Tup3> non_intersecting_rows;
    if(x1==x2)
    {
        // for(int y=y1;y<y2;y++)
        for(int y=std::min(y1,y2);y<=std::max(y1,y2);y++)
        {
            vector<Tup3> temp1=check_row_all_points_each(x1,y,0,my_turn);
            non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());
        }
    }
    else if(y1==y2)
    {
        for(int x=std::min(x1,x2);x<=std::max(x1,x2);x++)
        {
            vector<Tup3> temp1=check_row_all_points_each(x,y1,1,my_turn);
            non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());
        }
    }
    else
    {
        for(int i=std::min(x1,x2);i<=std::max(x1,x2);i++)
        {
            vector<Tup3> temp1=check_row_all_points_each(i,i+y1-x1,2,my_turn);
            non_intersecting_rows.insert(non_intersecting_rows.end(),temp1.begin(),temp1.end());   
        }
    }
    return non_intersecting_rows;    
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below check_row_all_points\n";

}

vector<MoveVal> Board::find_neighbours( Cart c, int dir, bool my_turn)//c--> position of ring to be moved
 {
  // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above find_neighbours\n";

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
    if ((x< 0|| y<0 || x>2*board_size || y>2*board_size)){
    
        // cerr << "Returning neighbours" << endl;
        return ch.neighbours;
    }

    MoveVal mvl;
    while(!(mapping[y][x]=="R" || mapping[y][x]=="RO" ||mapping[y][x]=="I"))
    {
        // cerr << "NEW ";
        // cerr << mapping[y][x] << " t " << t << endl;
         
        if(mapping[y][x]=="E" && t==0)
        {
            // cerr << "IF" << endl;
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
            // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above execute\n";
            execute_move_sequence(ct,m,my_turn);
            // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below execute\n";
            // cerr << "Initial Move Executed" << endl;
            vector<Tup3> t_vec;
            if(x==c.x)
            {
                t_vec = check_row_vertical(c.x,c.y, my_turn);
            }
            else if(y==c.y)
            {
                t_vec = check_row_horizontal(c.x,c.y, my_turn);
            }
            else
            {
                t_vec = check_row_diagonal(c.x,c.y, my_turn);
            }

            // for()
            // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above check\n";
            vector<Tup3> non_intersecting_rows = check_row_all_points(c.x,c.y,x,y,my_turn);
            // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below check\n";

            non_intersecting_rows.insert(non_intersecting_rows.end(),t_vec.begin(),t_vec.end());
            // cerr << "non_intersecting_rows" << endl;
             

            if(non_intersecting_rows.size() > 0)
                {
                    
                    for(int i=0;i<non_intersecting_rows.size();i++)
                    {
                        vector<string> m_temp_1;
                        vector<Cart> ct_temp_1;
                        vector<string> m_first;
                        vector<Cart> ct_first;

                        m_first.push_back("RS");
                        m_first.push_back("RE");
                        m_first.push_back("X");
                        m.push_back("RS");
                        m.push_back("RE");
                        m.push_back("X");

                        ct.push_back(non_intersecting_rows[i].carts[0]);
                        ct.push_back(non_intersecting_rows[i].carts[1]);
                        ct.push_back(non_intersecting_rows[i].carts[2]);
                        ct_first.push_back(non_intersecting_rows[i].carts[0]);
                        ct_first.push_back(non_intersecting_rows[i].carts[1]);
                        ct_first.push_back(non_intersecting_rows[i].carts[2]);
                                    // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above execute1\n";
                        execute_move_sequence(ct_first,m_first, my_turn);
                                    // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below execute1\n";

                        for(int j=i+1;j<non_intersecting_rows.size();j++)
                        {
                            vector<string> m_temp_2;
                            vector<Cart> ct_temp_2;
                            if(check_if_row(non_intersecting_rows[j].carts[0].x, 
                                            non_intersecting_rows[j].carts[0].y, 
                                            non_intersecting_rows[j].carts[1].x, 
                                            non_intersecting_rows[j].carts[1].y,
                                            non_intersecting_rows[j].carts[2].x, 
                                            non_intersecting_rows[j].carts[2].y,
                                            my_turn) ==0)
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

                                m_temp_2.push_back("RS");
                                m_temp_2.push_back("RE");
                                m_temp_2.push_back("X");
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[0]);
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[1]);
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[2]);



                                if(my_turn)
                                {
                                    if((m_temp_1.size()/3 + 1)>(RingPos.size()- (rings_max-3))) break;
                                }
                                else
                                {
                                    if((m_temp_1.size()/3 + 1)>(RingPosOpp.size()- (rings_max-3))) break;   
                                }
                                            // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above execute2\n";

                                execute_move_sequence(ct_temp_2, m_temp_2, my_turn);
                                    // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above execute2\n";
                                
                            }                                                      
                        }
                        // execute_move_sequence(ct_temp_1, m_temp_1, my_turn);
                        mvl.movetype = m;
                        mvl.cart_xy = ct;
                        ch.neighbours.push_back(mvl);
                                    // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above undo\n";

                        undo_move_sequence( ct_temp_1,m_temp_1, my_turn); 
                                    // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below undo\n";

                        undo_move_sequence(ct_first,m_first, my_turn);
                                    // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below undo1\n";

                        int len = m_temp_1.size();
                        for (int d = 0 ; d<len + 3; d++){//<= as 1 extra for initial
                            m.pop_back();
                            ct.pop_back();
                        }

                    }
                }
  
                else
                {
                    // cerr << "size = 0" << endl;
                    mvl.movetype = m;
                    mvl.cart_xy = ct;
                    ch.neighbours.push_back(mvl);
                }
                            // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " above undo_temp\n";

                undo_move_sequence(ct_temp,m_temp, my_turn);

            // cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below undo_temp\n";
                
            // cerr << "UNDOO" << endl;
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
            // cerr << "UNDOO" << endl;

        }
        else if(mapping[y][x]=="M" || mapping[y][x]=="MO")
        {
            // cerr << "ELSE IF" << endl;
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
            // cerr << "Break wala else if" << endl;
            // cerr << "IF" << endl;
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
            // cerr << "Initial Move Executed" << endl;
            vector<Tup3> t_vec;
            if(x==c.x)
            {
                t_vec = check_row_vertical(c.x,c.y,my_turn);
            }
            else if(y==c.y)
            {
                t_vec = check_row_horizontal(c.x,c.y,my_turn);
            }
            else
            {
                t_vec = check_row_diagonal(c.x,c.y,my_turn);
            }


            vector<Tup3> non_intersecting_rows = check_row_all_points(c.x,c.y,x,y,my_turn);
            non_intersecting_rows.insert(non_intersecting_rows.end(),t_vec.begin(),t_vec.end());
            // cerr << "non_intersecting_rows" << endl;
            if(non_intersecting_rows.size() > 0)
                {
                    
                    for(int i=0;i<non_intersecting_rows.size();i++)
                    {
                        vector<string> m_temp_1;
                        vector<Cart> ct_temp_1;
                        vector<string> m_first;
                        vector<Cart> ct_first;

                        m_first.push_back("RS");
                        m_first.push_back("RE");
                        m_first.push_back("X");
                        m.push_back("RS");
                        m.push_back("RE");
                        m.push_back("X");

                        ct.push_back(non_intersecting_rows[i].carts[0]);
                        ct.push_back(non_intersecting_rows[i].carts[1]);
                        ct.push_back(non_intersecting_rows[i].carts[2]);
                        ct_first.push_back(non_intersecting_rows[i].carts[0]);
                        ct_first.push_back(non_intersecting_rows[i].carts[1]);
                        ct_first.push_back(non_intersecting_rows[i].carts[2]);
                        execute_move_sequence(ct_first,m_first, my_turn);
                        
                        for(int j=i+1;j<non_intersecting_rows.size();j++)
                        {
                            vector<string> m_temp_2;
                            vector<Cart> ct_temp_2;
                            if(check_if_row(non_intersecting_rows[j].carts[0].x, 
                                            non_intersecting_rows[j].carts[0].y, 
                                            non_intersecting_rows[j].carts[1].x, 
                                            non_intersecting_rows[j].carts[1].y,
                                            non_intersecting_rows[j].carts[2].x, 
                                            non_intersecting_rows[j].carts[2].y,
                                            my_turn) ==0)
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

                                m_temp_2.push_back("RS");
                                m_temp_2.push_back("RE");
                                m_temp_2.push_back("X");
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[0]);
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[1]);
                                ct_temp_2.push_back(non_intersecting_rows[j].carts[2]);



                                if(my_turn)
                                {
                                    if((m_temp_1.size()/3 + 1)>(RingPos.size()- (rings_max-3))) break;
                                }
                                else
                                {
                                    if((m_temp_1.size()/3 + 1)>(RingPosOpp.size()- (rings_max-3))) break;   
                                }
                                execute_move_sequence(ct_temp_2, m_temp_2, my_turn);
                                
                            }                                                      
                        }
                        // execute_move_sequence(ct_temp_1, m_temp_1, my_turn);
                        mvl.movetype = m;
                        mvl.cart_xy = ct;
                        ch.neighbours.push_back(mvl);
                        undo_move_sequence( ct_temp_1,m_temp_1, my_turn); 
                        undo_move_sequence(ct_first,m_first, my_turn);
                        int len = m_temp_1.size();
                        for (int d = 0 ; d<len+3; d++){//<= as 1 extra for initial
                            m.pop_back();
                            ct.pop_back();
                        }

                    }
                }
                
                else
                {
                    // cerr << "size = 0" << endl;
                    mvl.movetype = m;
                    mvl.cart_xy = ct;
                    ch.neighbours.push_back(mvl);
                }

            undo_move_sequence(ct_temp,m_temp, my_turn);
            break;  
        }
        // cerr << x << ", " << y << endl;
        if ((x<0 || y<0 || x>(2*board_size) || y>(2*board_size))){
            break;
        }
    }
    // cerr << "Returning neighbours" << endl;
    return ch.neighbours;
// cerr << "MarkersMy: " << markersMy << "MarkersOpp: " << markersOpp << " below find_neighbours\n";
}

vector<MoveVal> Board::moveRing(bool my_turn)
{


    vector<MoveVal> padosi;

    vector<Cart> myCopyRing (RingPos);
    vector<Cart> oppCopyRing (RingPosOpp);

    if (my_turn){

        for (int i=0; i < RingPos.size(); i++) 
        {
            for(int j=1;j<=6;j++)
            {
                // cerr << "Next Dir" << i << ", " << j << endl;
                // printConfig();
                vector<MoveVal> p1= find_neighbours(myCopyRing[i],j, my_turn);
                // for (int w = 0; w< p1.size(); w++){
                //     for (int i = 0; i < p1[w].movetype.size(); ++i)
                //     {
                //         cerr << p1[w].movetype[i] << " " << p1[w].cart_xy[i].x << " "<< p1[w].cart_xy[i].y ;
                //     }
                //     cerr << endl;                
                // }
                padosi.insert(padosi.end(),p1.begin(),p1.end());  
            }
        }
    } 
    else{
        for (int i=0; i < RingPosOpp.size(); i++) 
        {
            for(int j=1;j<=6;j++)
            {
                // cerr << "Next Dir in Opp" << i << ", " << j << endl;
                // printConfig();

                vector<MoveVal> p1= find_neighbours(oppCopyRing[i],j, my_turn);
                // for (int w = 0; w< p1.size(); w++){
                //     for (int i = 0; i < p1[w].movetype.size(); ++i)
                //     {
                //         cerr << p1[w].movetype[i] << " " << p1[w].cart_xy[i].x << " "<< p1[w].cart_xy[i].y ;
                //     }
                //     cerr << endl;                
                // }
                padosi.insert(padosi.end(),p1.begin(),p1.end());

            }
        }
    } 
    
    return padosi; 
}


vector<MoveVal> Board::placeRing(bool my_turn){
  // cerr << "Place Ring Called" <<endl;
 /**/
  vector<MoveVal> all_possible_moves;
  int rings_temp = RingPos.size();
  cerr << rings_temp << " = No. of Rings Placed" << endl;
  cerr << "board_size = " << board_size << " rings_max = " << rings_max << " seq_length = " << seq_length << endl;
  
  if( rings_temp<rings_max-1)
  {
       
       MoveVal move;
       if(mapping[board_size][board_size]=="E")
       {
           Cart c;
           cerr << "Case 1: " << endl;
           c.x=board_size;
           c.y=board_size;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[ (board_size + 1)][board_size] == "E")
       {
           Cart c;
           cerr << "Case 2: " << endl;
           c.x=board_size;
           c.y= (board_size + 1);
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[ (board_size + 1)][(board_size + 1)] == "E")
       {
           Cart c;
           cerr << "Case 3: " << endl;
           c.x= (board_size + 1);
           c.y= (board_size + 1);
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[board_size][ (board_size + 1)] == "E")
       {
           Cart c;
           c.x= (board_size + 1);
           cerr << "Case 4: " << endl;
           c.y=board_size;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[(board_size - 1)][board_size] == "E")
       {
           cerr << "Case 5: " << endl;
           Cart c;
           c.x=board_size;
           c.y=(board_size - 1);
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[(board_size - 1)][(board_size - 1)] == "E")
       {
           cerr << "Case 6: " << endl;
           Cart c;
           c.x=(board_size - 1);
           c.y=(board_size - 1);
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[board_size][(board_size - 1)] == "E")
       {
           cerr << "Case 7: " << endl;
           Cart c;
           c.x=(board_size - 1);
           c.y=board_size;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[board_size + 2][board_size] == "E")
       {
           cerr << "Case 8: " << endl;
           Cart c;
           c.x=board_size;
           c.y=board_size + 2;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[board_size + 1][board_size - 1] == "E")
       {
           cerr << "Case 9: " << endl;
           Cart c;
           c.x=board_size - 1;
           c.y=board_size + 1;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
       else if (mapping[board_size - 1][board_size + 1] == "E")
       {
           cerr << "Case 10: " << endl;
           Cart c;
           c.x=board_size + 1;
           c.y=board_size - 1;
           move.movetype.push_back("P");
           move.cart_xy.push_back(c);
           // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
           all_possible_moves.push_back(move);
           return all_possible_moves;
       }
    }

  else
  {
      for(int y=0;y<=3;y++)
      {

          if(mapping[y+ (board_size + 1)][2*board_size]=="E")
          {
              MoveVal move;
              Cart c;
              c.x=2*board_size;
              c.y=y+ (board_size + 1);
              move.movetype.push_back("P");
              move.cart_xy.push_back(c);
              // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
              all_possible_moves.push_back(move);
              return all_possible_moves;;
          }
          if(mapping[y+1][0]=="E")
          {
              MoveVal move;
              Cart c;
              c.x=0;
              c.y=y+1;
              move.movetype.push_back("P");
              move.cart_xy.push_back(c);
              // execute_move_sequence(move.cart_xy, move.movetype, my_turn);
              all_possible_moves.push_back(move);
              return all_possible_moves;;
          }
      }
  }
  
}

     //------------------------------------Checkin rows made by opponent----------------------------------------------------            
Tup3 Board::CheckRowsMadeByOpp(Cart opp_c_in, Cart opp_c_fin, bool my_turn){


    vector<Tup3> non_intersecting_rows_by_opp = check_row_all_points(opp_c_in.x,opp_c_in.y,opp_c_fin.x,opp_c_fin.y,my_turn);
     Tup3 t;
    for(int j=0;j<non_intersecting_rows_by_opp.size();j++)
        {
            if(check_if_row(non_intersecting_rows_by_opp[j].carts[0].x,
                            non_intersecting_rows_by_opp[j].carts[0].y,
                            non_intersecting_rows_by_opp[j].carts[1].x,
                            non_intersecting_rows_by_opp[j].carts[1].y,
                            non_intersecting_rows_by_opp[j].carts[2].x,
                            non_intersecting_rows_by_opp[j].carts[2].y,
                            my_turn) == 0)

            {
                t.moves.push_back("RS");
                t.moves.push_back("RE");
                t.moves.push_back("X");
                t.carts.push_back(non_intersecting_rows_by_opp[j].carts[0]);
                t.carts.push_back(non_intersecting_rows_by_opp[j].carts[1]);
                t.carts.push_back(non_intersecting_rows_by_opp[j].carts[2]);
                // if(t.moves.size()/3 == RingPos.size()- 2) break; //REMOVING BREAK CONDITION
            }                       
        }

    // execute_move_sequence(t.carts,t.moves,my_turn);
    return t;
}

Children Board::find_children(int playerstate, bool my_turn)
{
    Children my_children;
    vector<MoveVal> p = moveRing(my_turn);
    // cerr << "Vector of Move Val Returned" << endl;
    my_children.neighbours = p;
    my_children.next_state = 2;
    return my_children;

    // }
    // if(playerstate==3)
    // {
    // }
}

    