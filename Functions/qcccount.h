static inline int zerocols2(const val_t P){
const val_t s=board[P];
return ((diagL[s+P])+diagR[s+(N-P)])==2;
}
//queen collisons at position: 2=none,2+=collision
static inline val_t qccount(val_t P){
//cannot be zero due being set from q[]
val_t s=board[P];
return (((diagL[s+P]))+((diagR[s+(N-P)])))-2;}

static inline val_t qrcount(val_t P){
//raw count of collisions
val_t s=board[P];
return (((diagL[s+P]))+((diagR[s+(N-P)])));}

