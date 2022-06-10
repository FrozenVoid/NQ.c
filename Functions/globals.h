typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;

int nosolve=0,fileload=0,scram=0,doprint=0,dofile=0;
val_t N,A=0,B=1;
val_t * board;
val_t * diagL;i64 sumL=0;
val_t * diagR;i64 sumR=0;
u64 tfail=0, swapt=0,tswaps=0,Blim,edge;
i64   fail=0;
size_t cend,cur,best;
size_t NL; u64 failmax;
