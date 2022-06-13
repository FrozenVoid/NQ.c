static inline int zerocols2( size_t P){
const size_t s=board[P];
return likely(((diagL[s+P])+diagR[s+(N-P)])==2);
}
//queen collisons at position: 2=none,2+=collision
static inline size_t qccount(size_t P){
//cannot be zero due being set from q[]
const size_t s=board[P];
__builtin_prefetch(&diagL[s+P],0,0);
__builtin_prefetch(&diagR[s+(N-P)],0,0);
return (((diagL[s+P]))+((diagR[s+(N-P)])))-2;}

static inline size_t qrcount(size_t P){
//raw count of collisions
size_t s=board[P];
return (((diagL[s+P]))+((diagR[s+(N-P)])));}

