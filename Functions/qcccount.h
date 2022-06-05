//queen collisons at position: 2=none,2+=collision
static inline val_t qccount(val_t P){
//cannot be zero due being set from q[]
val_t s=board[P];
FETC(&diagL[s+P],0,0);
FETC(&diagR[s+(N-P)],0,0);
return ((diagL[s+P]))+((diagR[s+(N-P)]))-2;}
