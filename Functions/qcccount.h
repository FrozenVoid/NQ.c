//queen collisons at position: 2=none,2+=collision
static inline val_t qccount(val_t P){
//cannot be zero due being set from q[]
val_t s=board[P];
return ((diagL[s+P]))+((diagR[s+(N-P)]))-2;}
