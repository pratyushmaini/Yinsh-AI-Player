MinVal(state, alpha, beta){
if (terminal(state))
return utility(state);
for (s in children(state)){
child = MaxVal(s,alpha,beta);
beta = min(beta,child);
if (alpha>=beta) return child;
}
return best child (min); } 

MaxVal(state, alpha, beta){
if (terminal(state))
return utility(state);
for (s in children(state)){
child = MinVal(s,alpha,beta);
alpha = max(alpha,child);
if (alpha>=beta) return child;
}
return best child (max); }

function MiniMax(state){
	v = MaxVal(state);
	return action in Successors(state) with value v;
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
f1
(s) + w2
f2
(s) + … + wn
fn
(s)