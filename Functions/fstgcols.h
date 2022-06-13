//first greater than column(s) with collision
static inline size_t fstgcols( size_t G){
size_t i=G+1, maxN=N;;
fstgcolsloop:;
i=i==maxN?0:i;
const size_t s=board[i];
__builtin_prefetch(&diagL[s+i],0,0);
__builtin_prefetch(&diagR[s+(maxN-i)],0,0);
if(unlikely((((diagL[s+i]))+((diagR[s+(maxN-i)])))-2))return i;
i++;goto fstgcolsloop;
}

