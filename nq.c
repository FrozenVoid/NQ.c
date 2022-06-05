#include "Util/void.h"//https://github.com/FrozenVoid/C-headers
//linear ~O(N) NQueens  solver

 size_t NCYCLES=1ULL<<32; //report each NCYCLES
#define MINBOARD 8
#ifdef NOPREFETCH
#define FETC(a...)
#else
#define FETC(a...) __builtin_prefetch(a)
#endif
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
#define rotate(num,bits) ({ typeof(num) x=num;\
x=(x>>bits)|(x<<((sizeof(x)*8)-bits));x;})
#define rndgen64 randuint64
int nosolve=0,fileload=0,scram=0,doprint=0,dofile=0;
val_t N,A=0,B=1;
val_t * board;
val_t * diagL;i64 sumL=0;
val_t * diagR;i64 sumR=0;
i64 swapt=0,swaps=0,checkb=0;
size_t  fail=0,tfail=0,dir=1,tswaps=0,cend,valr,cur,best;

#define swapq(x,y) ({val_t temp=x;x=y;y=temp;})


#include "Functions/swapc.h"
#include "Functions/qcccount.h"
#include "Functions/zerocols.h"
#include "Functions/fstcols.h"
#include "Functions/fstgcols.h"
#include "Functions/printboard.h"
#include "Functions/fileboard.h"
#include "Functions/fileloadfrom.h"
#include "Functions/modreduce.h"
#include "Functions/rndcell.h"
#include "Functions/info.h"
#include "Functions/lin.h"
#include "Functions/diags.h"
#include "Functions/solve.h"
#include "Functions/integrity.h"
#include "Functions/presolve.h"
#include "Functions/scramble.h"
#include "Functions/verifier.h"
#include "Functions/syntax.h"
#include "Functions/checkdup.h"
int main(int argc,char**argv){

if(argc<2){syntax();}
N=atoi(argv[1]);if(N<MINBOARD)syntax();
size_t colsize=sizeof(val_t)*N;
print("Queen board size=",colsize," bytes\n");
board=malloc(sizeof(val_t)*N);//columns
if(!board){perror("Queen array size too large for malloc");exit(2);}
fflush(stdout);
size_t diagsize=sizeof(val_t)*(N+2)*2;
print("Diagonal arrays size=",2*diagsize," bytes\n");
diagL=malloc(diagsize);
diagR=malloc(diagsize);
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}

if(argc>=3){
dofile= !!strchr(argv[2],'f');//file output
doprint=!!strchr(argv[2],'p');//print
 nosolve= !!strchr(argv[2],'t');//presolved
checkb=!!strchr(argv[2],'c');//pedantic check
scram=!! strchr(argv[2],'s');//scramble
print("Options:",dofile?"\nfile output":"",
doprint?"\nprint board rows":"",
nosolve?"\ngenerate presolved board":"",
checkb?"\npedantic checks":"",
scram?"\nscramble board":"");

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

//file input and scramble
if(fileload){fileloadfrom(argv[3]);}
if(scram){size_t scrnum=atoi(argv[2]);scramble(scrnum);}
//main func
print("\nSolver:\n");
if(checkb){checkdup();}
solve();
//check it
verifier();
if(checkb){checkdup();integrity();}
//output
if(doprint){char sep=',';
if(!fileload && argc==4)sep=argv[3][0];
printboard(sep);}
if(dofile){fileboard();}
return 0;}
