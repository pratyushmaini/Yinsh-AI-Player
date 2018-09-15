//State of the game :
//
class MoveVal{
    string movetype;
    Cart cart_xy;
    float utility;

    MoveVal(){

    }
    MoveVal(string m, Cart c, float u){
        movetype = m;
        cart_xy = c;
        utility = u;
    }
}
class Node {
    MoveVal move_val;
    Board board;

}

utility(state, prev_move){

}

DecisionMaker(state){
    v -> MaxVal(state)
    return action that gives v;
}
//MaxVal should return the action P 0 1 etc, the value

MinVal(state, alpha, beta, ply){
    if (terminal(state) || ply == 0)
        return utility(state);
    for (s in children(state)){
        child = MaxVal(s,alpha,beta, ply - 1);
        beta = min(beta,child);
    if (alpha>=beta) return child;
    }
    return best child (min); } 

MaxVal(state, alpha, beta, ply){
    if (terminal(state) || ply == 0)
        return utility(state);
    for (s in children(state)){
        child = MinVal(s,alpha,beta, ply - 1);
        alpha = max(alpha,child);
    if (alpha>=beta) 
        return child;
    }
    return best child (max); } 



class Pair
{
public:
    Cart c;int score;
    Pair(Cart ct, int s)
    {
        c=ct;
        score=s;
    }
}
class Tuple
{
public:
    Cart c1;Cart c2;
    Tuple(Cart r1, Cart r2)
    {
        c1=r1;
        c2=r2;
    }
}
class Node
{
    public:
        Board board;
        vector<Node> children;
        string move; 
        Node(Board bd,vector<Node> chldrn)
        {
            board=bd;
            children=chldrn;
        }
        bool terminal(Node n)
        {
            if(n.children.empty()) return true;
            return false;
        }
        int utility(Node n)
        {   
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
    Pair vuneighbours(Node state,Cart c,Cart fin_pos,int max_score)
    {
        int x=c.x;
        int y=c.y+1;
        int t=0;
        Pair p;
        p.score=max_score;
        p.c=fin_pos;
        while(!(state.board.mapping[x][y]=="R" ||state.board.mapping[x][y]=="RO" ||state.board.mapping[x][y]=="I"))
        {
            if(state.board.mapping[x][y]=="E" && t==0)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);//-------------------Make this function-------------------------------------------------------
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                y++;
            }
            else if(state.board.mapping[x][y]=="M" || state.board.mapping[x][y]=="MO")
            {
                t=1;
                y++;
            }
            else if(state.board.mapping[x][y]=="E" && t==1)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                break;  
            }
        }
        return p;
    }
    Pair vdneighbours(Node state,Cart c,Cart fin_pos,int max_score)
    {
        int x=c.x;
        int y=c.y-1;
        int t=0;
        Pair p;
        p.score=max_score;
        p.c=fin_pos,;
        while(!(state.board.mapping[x][y]=="R" ||state.board.mapping[x][y]=="RO" ||state.board.mapping[x][y]=="I"))
        {
            if(state.board.mapping[x][y]=="E" && t==0)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);//-------------------Make this function-------------------------------------------------------
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                y--;
            }
            else if(state.board.mapping[x][y]=="M" || state.board.mapping[x][y]=="MO")
            {
                t=1;
                y--;
            }
            else if(state.board.mapping[x][y]=="E" && t==1)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                break;  
            }
        }
        return p;
    }
    Pair hrneighbours(Node state,Cart c,Cart fin_pos,int max_score)
    {
        int x=c.x+1;
        int y=c.y;
        int t=0;
        Pair p;
        p.score=max_score;
        p.c=fin_pos,;
        while(!(state.board.mapping[x][y]=="R" ||state.board.mapping[x][y]=="RO" ||state.board.mapping[x][y]=="I"))
        {
            if(state.board.mapping[x][y]=="E" && t==0)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);//-------------------Make this function-------------------------------------------------------
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                x++;
            }
            else if(state.board.mapping[x][y]=="M" || state.board.mapping[x][y]=="MO")
            {
                t=1;
                x++;
            }
            else if(state.board.mapping[x][y]=="E" && t==1)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                break;  
            }
        }
        return p;
    }
    Pair hlneighbours(Node state,Cart c,Cart fin_pos,int max_score)
    {
        int x=c.x-1;
        int y=c.y;
        int t=0;
        Pair p;
        p.score=max_score;
        p.c=fin_pos,;
        while(!(state.board.mapping[x][y]=="R" ||state.board.mapping[x][y]=="RO" ||state.board.mapping[x][y]=="I"))
        {
            if(state.board.mapping[x][y]=="E" && t==0)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);//-------------------Make this function-------------------------------------------------------
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                x--;
            }
            else if(state.board.mapping[x][y]=="M" || state.board.mapping[x][y]=="MO")
            {
                t=1;
                x--;
            }
            else if(state.board.mapping[x][y]=="E" && t==1)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                break;  
            }
        }
        return p;
    }
    Pair duneighbours(Node state,Cart c,Cart fin_pos,int max_score)
    {
        int x=c.x+1;
        int y=c.y+1;
        int t=0;
        Pair p;
        p.score=max_score;
        p.c=fin_pos,;
        while(!(state.board.mapping[x][y]=="R" ||state.board.mapping[x][y]=="RO" ||state.board.mapping[x][y]=="I"))
        {
            if(state.board.mapping[x][y]=="E" && t==0)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);//-------------------Make this function-------------------------------------------------------
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                x++;y++;
            }
            else if(state.board.mapping[x][y]=="M" || state.board.mapping[x][y]=="MO")
            {
                t=1;
                x++;y++;
            }
            else if(state.board.mapping[x][y]=="E" && t==1)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                break;  
            }
        }
        return p;
    }
    Pair ddneighbours(Node state,Cart c,Cart fin_pos,int max_score)
    {
        int x=c.x-1;
        int y=c.y-1;
        int t=0;
        Pair p;
        p.score=max_score;
        p.c=fin_pos,;
        while(!(state.board.mapping[x][y]=="R" ||state.board.mapping[x][y]=="RO" ||state.board.mapping[x][y]=="I"))
        {
            if(state.board.mapping[x][y]=="E" && t==0)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);//-------------------Make this function-------------------------------------------------------
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                x--;y--;
            }
            else if(state.board.mapping[x][y]=="M" || state.board.mapping[x][y]=="MO")
            {
                t=1;
                x--;y--;
            }
            else if(state.board.mapping[x][y]=="E" && t==1)
            {
                Cart r;
                r.x=x;r.y=y;
                vector<vector<string>> temp=state.board.mapping;
                temp[c.x][c.y]="M";
                temp[x][y]="R";
                int score=calculate_utility(temp);
                if(score>max)
                {
                    p.c=r;
                    p.score=score;
                }
                break;  
            }
        }
        return p;
    }
    Tuple moveRing(Node state)
    {
        vector<Cart> rings= state.board.RingPos;
        Cart final_pos;
        final_pos.x=-1;
        final_pos.y=-1;
        int score=INT_MIN;
        Cart init_pos; 
        Pair p;
        p.c=final_pos;
        p.score=score+1;
        for (auto i = rings.begin(); i != rings.end(); ++i) 
        {
            if(p.score>score) {init_pos=i;score=p.score;}
            p=vuneighbours(state,i,p.c,p.score);
            p=vdneighbours(state,i,p.c,p.score);
            p=hrneighbours(state,i,p.c,p.score);
            p=hlneighbours(state,i,p.c,p.score);
            p=duneighbours(state,i,p.c,p.score);
            p=ddneighbours(state,i,p.c,p.score);
        }
        if(p.score>score) init_pos=i;
        Tuple t;
        t.c1=init_pos;
        t.c2=p.c;
        return t; 
    }
    // bool check_row(Node state, Cart init_pos, Cart final_pos )
    // {
    //     vector<>
    // }
    string makeMove(Node state, int playerstate)
    {
        string s="";
        if(playerstate==1)
        {
            s=s+"P";
            Cart c=placeRing(state); 
        }
        if(playerstate==2)
        {
            Tuple t=moveRing(state);
            Cart init_pos=t.c1;
            Cart final_pos=t.c2;
            s=s+"S"+" "+init_pos.x+" "+init_pos.y+" ";
            s=s+"M"+" "+final_pos.x+" "+final_pos.y+" ";
            if(check_row(state, init_pos,final_pos)) playerstate=3;
        }
        if(playerstate==3)
        {
        }
    }
}
//Bad and Good Cases for Alpha-Beta Pruning
/*Terminal? is replaced by Cutoff?
2. Utility is replaced by Eval
Does it work in practice?
b
m = 106
, b=35  m=4
4-ply lookahead is a hopeless chess player!
– 4-ply ≈ human novice
– 8-ply ≈ typical PC, human master
– 12-ply ≈ Deep Blue, Kasparov
*/
//Eval(s) = w1
/*
f1
(s) + w2
f2
(s) + … + wn
fn
(s)

 */