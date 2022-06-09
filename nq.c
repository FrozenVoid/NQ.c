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
#define setdir(x) dir=x;
#define addswap(x) swapt+=x;
#define setswaps(x) swaps=x;
#define incfails() tfail++;
#else
#define setswaps(x) ;
#define setdir(x) ;
#define addswap(x) ;
#define incfails() ;
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
i64 swapt=0,swaps=0;
u64 tfail=0,tswaps=0,Blim;
i64   fail=0,dir=1;
size_t cend,valr,cur,best;
size_t NL; u64 lc,lcmax,failmax,endsearch;

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

int main(int argc,char**argv){

if(argc<2){syntax();}
N=(val_t)strtoull(argv[1],NULL,10);
if(N<MINBOARD)syntax();
size_t colsize=sizeof(val_t)*N;
print("Queen board size=",colsize," bytes\n");

board=calloc(colsize,1);//columns
if(!board){perror("Queen array size too large for malloc");exit(2);}
fflush(stdout);
size_t diagsize=sizeof(val_t)*(N)*2;
print("Diagonal arrays size=",2*diagsize," bytes\n");
diagL=calloc(diagsize,1);
diagR=calloc(diagsize,1);
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}

if(argc>=3){
dofile= !!strchr(argv[2],'f');//file output
doprint=!!strchr(argv[2],'p');//print
 nosolve= !!strchr(argv[2],'t');//presolved
checkb=!!strchr(argv[2],'c');//pedantic check
scram=!! strchr(argv[2],'s');//scramble

}

#ifdef NOPREFETCH
print("\nprefetch disabled");
#endif
#ifdef SILENCE
print("\ninfo() disabled");
#endif
 if(argc==4){//file input
 fileload=!!strchr(argv[2],'i');}
//setup board
if(nosolve){setpresolved();}
else if(!fileload){for(size_t i=0;i<N;i++)board[i]=i;}

print(dofile?"\n[x]file output":"",
doprint?"\n[x]print board rows":"",
nosolve?"\n[x]generate presolved board":"",
checkb?"\n[x]pedantic checks":"",
scram?"\n[x]scramble board":"");

//file input and scramble
if(fileload){fileloadfrom(argv[3]);}
//main func
if(checkb||fileload ){;checkdup();}
if(scram){size_t scrnum=atoi(argv[2]);scramble(scrnum);}
print("\nSolver:\n");solve();
//check it
verifier();
if(checkb){integrity();checkdup();}
//output
if(doprint){char sep=',';
if(!fileload && argc==4)sep=argv[3][0];
printboard(sep);
if(N<64)printgraph();
}
if(dofile){fileboard();}
return 0;}
