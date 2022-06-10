//linear ~O(N) NQueens  solver
#define log2index(x)  (63 - __builtin_clzll((x)))


#define unlikely(x) __builtin_expect(x,0)
#define likely(x) __builtin_expect(x,1)

#ifndef NCYCLES
#define NCYCLES (1ULL<<32) //report each NCYCLES
#endif


#ifdef USEPREFETCH
#define FETC(a...) __builtin_prefetch(a)
#else
#define FETC(a...)
#endif

#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#ifdef BIGIRON
#define val_t u64
#define sortmethod combsort
#define modreduce range
#else
#define val_t u32
#define modreduce range32b
#define sortmethod combsort
#endif
//----linear collission count----------
#define countudiag() (sumL+sumR)
#define zerocols(P) (!qccount(P))

#define rndcell()  modreduce(N)
#define rndedgecell(X) ({val_t startX=X*(X+edge<N);startX+modreduce(N-startX);})
#define swapq(x,y) ({val_t temp=board[x];board[x]=board[y];board[y]=temp;})
#ifndef SILENCE
#define incswap() swapt++;
#define incfails() tfail++;
void info(char* data);
#else
#define incfails() ;
#define incswap() ;
#endif
#ifndef VERBOSE
#define verbprint(...)
#define verbinfo(...)
#else
#define verbprint print
#define verbinfo info
#endif
