//first greater than column(s) with collision
static inline const val_t fstgcols( val_t G){
size_t i=G+1, maxN=N;;
fstgcolsloop:;
if(likely(i==maxN)){i=0;goto fstgcolsloop;}
const size_t s=board[i];
__builtin_prefetch(&diagL[s+i],0,0);
__builtin_prefetch(&diagR[s+(maxN-i)],0,0);
if(unlikely((((diagL[s+i]))+((diagR[s+(maxN-i)])))-2))return i;
i++;goto fstgcolsloop;
return i;/*compiler likes end return struct*/}

