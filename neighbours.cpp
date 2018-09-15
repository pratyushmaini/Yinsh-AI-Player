#include "minimax.h"
#include <vector>
using namespace std;
#include<bits/stdc++.h> 

class Pair
{
public:
    vector<vector<string>> move;vector<vector<Cart>> cart;
    Pair(vector<vector<string>> m, vector<vector<Cart>> c)
    {
        move=m;
        cart=c;//----------------------------------------Do this correctly-------------------------------
    }
}
class Tup3 
{
public:
    bool b;vector<string> moves; vector<Cart> carts;
    Tup3(bool bo;vector<string> m; vector<Cart> c)
    {
        b=bo;
        moves=m;
        carts=c;
    }
}

class Move
{
    int MinVal(Node state,int a,int b)
    {
        int alpha=a;
        int beta=b;
        if (terminal(state)) 
            return utility(state);
        for (int i=0;i<state.children.size();i++)
        {
            Node s=chidren.at(i);
            int child = MaxVal(s,alpha,beta);
            beta=std::min(beta,child);
            if (alpha>=beta) return child;
        }
        return beta; 
    } 
    int MaxVal(Node state,int alpha,int beta)
    {
        if (terminal(state))
            return utility(state);
        for (int i=0;i<state.children.size();i++)
        {
            Node s=chidren.at(i);
            int child = MinVal(s,alpha,beta);
            alpha = std::max(alpha,child);
            if (alpha>=beta) return child;
        }
        return alpha;
    }
    string MiniMax(Node state)
    {
        v = MaxVal(state,INT_MIN, INT_MAX);
        return action in Successors(state) with value v;
    }
    Tup3 check_row(vector<vector<string>> map, int init_pos_x,int init_pos_y,int final_pos_x, int final_pos_y )
    {
        int x1=init_pos_x;int y1=init_pos_y;
        int x2=final_pos_x;int y2=final_pos_y;
        map[x1][y1]="M";
        map[x2][y2]="R";
        Tup3 t;
        t.b=false;
        flip(map,x1,y1,x2,y2);//------------------------------------------------check with maini--------------------------
        int h=0;int hip=0;int v=0;int vip=0;//h-->conseq. hor markers// hip =1--> indicates whether a row is in progress
        for(int i=0;i<=10;i++)
        {
            if(map[x][i]=="M") 
                {
                    h++;hip=1;
                    if(h==5)
                    {
                        t.b=true;
                        Cart c1;c1.x=x;c1.y=i;Cart c2;c2.x=x;c2.y=i-5;
                        t.moves.push_back("RS");t.moves.push_back("RE");
                        t.carts.push_back(c1);t.carts.push_back(c2);
                        map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(c);
                    }
                }
            else{h=0;hip=0;}
        }
        for(i=0;i<10-std::abs(x1-y1);i++)
        {
            if(x1>=y1)
            {
                if(map[x1-y1+i][i]=="M") 
                {
                    h++;hip=1;
                    if(h==5)
                    {
                        t.b=true;
                        Cart c1;c1.x=x1-y1+i;c1.y=i;Cart c2;c2.x=x1-y1+i-5;c2.y=i-5;
                        t.moves.push_back("RS");t.moves.push_back("RE");
                        t.carts.push_back(c1);t.carts.push_back(c2);
                        map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(c);
                    }
                }
                else{h=0;hip=0;}
            }
            else
            {
                if(map[i][y1-x1+i]=="M") 
                {
                    h++;hip=1;
                    if(h==5)
                    {
                        t.b=true;
                        Cart c1;c1.x=i;c1.y=y1-x1+i;Cart c2;c2.x=i-5;c2.y=y1-x1+i-5;
                        t.moves.push_back("RS");t.moves.push_back("RE");
                        t.carts.push_back(c1);t.carts.push_back(c2);
                        map=removeRow(map,c1,c2);//------------------------------Make this--------------------------------------
                        Cart c=removeRing(map);//--------------------------------Make This--------------------------------------
                        t.moves.push_back("X");
                        t.carts.push_back(c);
                    }
                }
                else{h=0;hip=0;}
            }
        }
        return t;
    }
    Pair vuneighbours(Board board,Cart c)//c--> position of ring to be moved
    {
        int x=c.x;
        int y=c.y+1;
        int t=0;
        Pair p;
        while(!(board.mapping[x][y]=="R" ||board.mapping[x][y]=="RO" ||board.mapping[x][y]=="I"))
        {
            if(board.mapping[x][y]=="E" && t==0)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                y++;
            }
            else if(board.mapping[x][y]=="M" || board.mapping[x][y]=="MO")
            {
                t=1;
                y++;
            }
            else if(board.mapping[x][y]=="E" && t==1)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                break;  
            }
        }
        return p;
    }
    Pair vdneighbours(Board board,Cart c)//c--> position of ring to be moved
    {
        int x=c.x;
        int y=c.y-1;
        int t=0;
        Pair p;
        while(!(board.mapping[x][y]=="R" ||board.mapping[x][y]=="RO" ||board.mapping[x][y]=="I"))
        {
            if(board.mapping[x][y]=="E" && t==0)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                y--;
            }
            else if(board.mapping[x][y]=="M" || board.mapping[x][y]=="MO")
            {
                t=1;
                y--;
            }
            else if(board.mapping[x][y]=="E" && t==1)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                break;  
            }
        }
        return p;
    }
    Pair hrneighbours(Board board,Cart c)//c--> position of ring to be moved
    {
        int x=c.x+1;
        int y=c.y;
        int t=0;
        Pair p;
        while(!(board.mapping[x][y]=="R" ||board.mapping[x][y]=="RO" ||board.mapping[x][y]=="I"))
        {
            if(board.mapping[x][y]=="E" && t==0)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                x++;
            }
            else if(board.mapping[x][y]=="M" || board.mapping[x][y]=="MO")
            {
                t=1;
                x++;
            }
            else if(board.mapping[x][y]=="E" && t==1)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                break;  
            }
        }
        return p;
    }
    Pair hlneighbours(Board board,Cart c)//c--> position of ring to be moved
    {
        int x=c.x-1;
        int y=c.y;
        int t=0;
        Pair p;
        while(!(board.mapping[x][y]=="R" ||board.mapping[x][y]=="RO" ||board.mapping[x][y]=="I"))
        {
            if(board.mapping[x][y]=="E" && t==0)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                x--;
            }
            else if(board.mapping[x][y]=="M" || board.mapping[x][y]=="MO")
            {
                t=1;
                x--;
            }
            else if(board.mapping[x][y]=="E" && t==1)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                break;  
            }
        }
        return p;
    }
    Pair duneighbours(Board board,Cart c)//c--> position of ring to be moved
    {
        int x=c.x+1;
        int y=c.y+1;
        int t=0;
        Pair p;
        while(!(board.mapping[x][y]=="R" ||board.mapping[x][y]=="RO" ||board.mapping[x][y]=="I"))
        {
            if(board.mapping[x][y]=="E" && t==0)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                x++;y++;
            }
            else if(board.mapping[x][y]=="M" || board.mapping[x][y]=="MO")
            {
                t=1;
                x++;y++;
            }
            else if(board.mapping[x][y]=="E" && t==1)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                break;  
            }
        }
        return p;
    }
    Pair ddneighbours(Board board,Cart c)//c--> position of ring to be moved
    {
        int x=c.x-1;
        int y=c.y-1;
        int t=0;
        Pair p;
        while(!(board.mapping[x][y]=="R" ||board.mapping[x][y]=="RO" ||board.mapping[x][y]=="I"))
        {
            if(board.mapping[x][y]=="E" && t==0)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                x--;y--;
            }
            else if(board.mapping[x][y]=="M" || board.mapping[x][y]=="MO")
            {
                t=1;
                x--;y--;
            }
            else if(board.mapping[x][y]=="E" && t==1)
            {
                vector<string> m;
                vector<Cart> ct;
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                m.push_back("S");m.push_back("M");
                ct.push_back(c);ct.push_back(r);
                Tup3 t=check_row(temp,c.x,c.y,x,y)
                if(t.b==true)
                {
                    m.insert(m.end(),t.moves.begin(),t.moves.end());
                    ct.insert(ct.end(),t.carts.begin(),t.carts.end());          
                }
                p.move.push_back(m);
                p.cart.push_back(ct);
                break;  
            }
        }
        return p;
    }
    Pair moveRing(Board board)
    {
        vector<Cart> rings= board.RingPos;
        Cart init_pos;
        Pair p; 
        vector<vector<string>> moves;
        vector<vector<Cart>> cart;
        for (auto i = rings.begin(); i != rings.end(); ++i) 
        {
            Pair p1=vuneighbours(state,i);
            p.move.insert(p.move.end(),p1.move.begin(),p1.move.end());
            p.cart.insert(p.cart.end(),p1.cart.begin(),p1.cart.end());
            Pair p2=vdneighbours(state,i);
            p.move.insert(p.move.end(),p2.move.begin(),p2.move.end());
            p.cart.insert(p.cart.end(),p2.cart.begin(),p2.cart.end());
            Pair p3=hrneighbours(state,i);
            p.move.insert(p.move.end(),p3.move.begin(),p3.move.end());
            p.cart.insert(p.cart.end(),p3.cart.begin(),p3.cart.end());
            Pair p4=hlneighbours(state,i);
            p.move.insert(p.move.end(),p4.move.begin(),p4.move.end());
            p.cart.insert(p.cart.end(),p4.cart.begin(),p4.cart.end());
            Pair p5=duneighbours(state,i);
            p.move.insert(p.move.end(),p5.move.begin(),p5.move.end());
            p.cart.insert(p.cart.end(),p5.cart.begin(),p5.cart.end());
            Pair p6=ddneighbours(state,i);
            p.move.insert(p.move.end(),p6.move.begin(),p6.move.end());
            p.cart.insert(p.cart.end(),p6.cart.begin(),p6.cart.end());
            
        }
        return p; 
    }
     
    Children children(Board board, int playerstate)
    {
        if(playerstate==1)
        {
            Pair p=placeRing(board);
            return p; 
        }
        if(playerstate==2)
        {
            Pair p=moveRing(board);

            return p;
        }
        if(playerstate==3)
        {
        }
    }
}