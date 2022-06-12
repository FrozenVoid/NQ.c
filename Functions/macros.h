//linear ~O(N) NQueens  solver
#define log2index(x)  (63 - __builtin_clzll((x)))


#define unlikely(x) __builtin_expect(x,0)
#define likely(x) __builtin_expect(x,1)
#define SWAPLIMIT 8//below swapc ignores fails
#ifndef NCYCLES
#define NCYCLES (1ULL<<32) //report each NCYCLES
#endif
#define FLUSH //fflush(stdout);
#define NOINLINE __attribute__ ((noinline))
#ifdef USEPREFETCH
#define FETC(a...) __builtin_prefetch(a)
#else
#define FETC(a...)
#endif

#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#ifdef BIGIRON
#define val_t uint64_t
#define sortmethod combsort
#define modreduce range
#else
#define val_t uint32_t
#define modreduce range32b
#define sortmethod combsort
#endif

#define zerocols(P) (!qccount(P))

#define rndcell()  modreduce(N)


#ifndef SILENCE
#define incswap() swapt++;
#define decswap() swapt--;
#define incfails() tfail++;
void info(char* data);
#else
#define incfails() ;
#define incswap() ;
#define decswap() ;
#endif

#ifndef VERBOSE
#define verbprint(...)
#define verbinfo(...)
#else
#define verbprint print
#define verbinfo info
#endif
