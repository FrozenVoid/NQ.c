 int zerocols(val_t P){//1= no collision,>1 collisions
FETC(&board[P],0,0);
const val_t s=board[P];
FETC(&diagL[s+P],0,0);
if((diagL[s+P])!=1)return 0;
FETC(&diagR[s+(N-P)],0,0);
if(diagR[s+(N-P)]!=1)return 0;
return 1;
//return !((((diagL[s+P])) +(diagR[s+(N-P)]))-2);//1:1=
//return !((((diagL[s+P]))+((diagR[s+(N-P)])))-2);
}
