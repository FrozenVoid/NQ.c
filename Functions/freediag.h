
static inline int freediag(val_t P,val_t S){//Swapped/Position cells diagonals
FETC(&diagL[board[S]+P],0,0);
FETC(&diagR[board[S]+(N-P)],0,0);
FETC(&diagL[board[P]+S],0,0);
FETC(&diagR[board[P]+(N-S)],0,0	);

const int lP=!diagL[board[S]+P];
const int rP=!!diagR[board[S]+(N-P)];
const int lS=!diagL[board[P]+S];
const int rS=!!diagR[board[P]+(N-S)];
return lP+rP+lS+rS;
;}


