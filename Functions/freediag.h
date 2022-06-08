
static inline int freediag(val_t P,val_t S){//Swapped/Position cells diagonals

const val_t lP=!diagL[board[S]+P];
const val_t rP=!diagR[board[S]+(N-P)];
const val_t lS=!diagL[board[P]+S];
const val_t rS=!diagR[board[P]+(N-S)];
return lP+rP+lS+rS;
;}


