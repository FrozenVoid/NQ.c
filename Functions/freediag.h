
static inline int freediag(val_t P,val_t S){//Swapped/Position cells diagonals
FETC(&diagL[board[S]+P]);
FETC(&diagR[board[S]+(N-P)]);
FETC(&diagL[board[P]+S]);
FETC(&diagR[board[P]+(N-S)]);

 val_t lP=!diagL[board[S]+P];
 val_t rP=!!diagR[board[S]+(N-P)];
 val_t lS=!diagL[board[P]+S];
 val_t rS=!!diagR[board[P]+(N-S)];
return lP+rP+lS+rS;
;}


