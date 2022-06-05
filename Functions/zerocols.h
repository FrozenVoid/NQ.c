static inline int zerocols(val_t P){//1= no collision,>1 collisions
const val_t s=board[P];
if((diagL[s+P])!=1)return 0;
if(diagR[s+(N-P)]!=1)return 0;
return 1;}
