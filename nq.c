#include "standalone/print.h"
#include "standalone/random.h"
#include "standalone/combsort.h"
#include "standalone/hitstat.h"
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>//__rdtsc
typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
//linear ~O(N) NQueens  solver
#define log2index(x)  (63 - __builtin_clzll((x)))


#define unlikely(x) __builtin_expect(x,0)
#define likely(x) __builtin_expect(x,1)
#define zerocols(P) (!qccount(P))
//#define fstgcols(P)  bitfirstfrom(bitcols,P+1)
 size_t NCYCLES=1ULL<<32; //report each NCYCLES
#define MINBOARD 8
//NOPREFETCH disabled
#define FETC(a...)
//#define FETC(a...) __builtin_prefetch(a)

#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#ifdef BIGIRON
#define val_t u64
#define sval_t unsigned __int128
#else
#define val_t u32
#define sval_t u64
#endif
//----linear collission count----------
#define countudiag() (sumL+sumR)
#define randuint64 rnd1
#ifndef SILENCE
#define incswap() swapt++;
#define incfails() tfail++;
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
#define rotate(num,bits) ({ typeof(num) x=num;\
x=(x>>bits)|(x<<((sizeof(x)*8)-bits));x;})


int nosolve=0,fileload=0,scram=0,doprint=0,dofile=0,checkb=0;
val_t N,A=0,B=1;
val_t * board;
val_t * diagL;i64 sumL=0;
val_t * diagR;i64 sumR=0;
u64 tfail=0, swapt=0,tswaps=0,Blim;
i64   fail=0;
size_t cend,cur,best;
size_t NL; u64 failmax;

void info(char* data);
#include "Functions/swapq.h"
#include "Functions/checkdup.h"
#include "Functions/qcccount.h"
#include "Functions/swapc.h"
#include "Functions/freediag.h"
#include "Functions/printboard.h"
#include "Functions/fileboard.h"
#include "Functions/fileloadfrom.h"
#include "Functions/fstgcols.h"
#include "Functions/modreduce.h"
#include "Functions/rndcell.h"
#include "Functions/info.h"
#include "Functions/fastdiagswap.h"
#include "Functions/lin.h"
#include "Functions/solve.h"
#include "Functions/integrity.h"
#include "Functions/presolve.h"
#include "Functions/scramble.h"
#include "Functions/verifier.h"
#include "Functions/syntax.h"
#include "Functions/main.h"
