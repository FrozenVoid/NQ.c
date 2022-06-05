#include "/home/user/Code/Util/void.h"//https://github.com/FrozenVoid/C-headers
//linear ~O(N) NQueens  solver

 size_t NCYCLES=1ULL<<32; //report each NCYCLES
#define MINBOARD 8
#ifdef PREFETCH
#define FETC(a...) __builtin_prefetch(a)
#else
#define FETC(a...)
#endif
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#ifdef BIGIRON
#define val_t u64
#define sval_t unsigned __int128
#else
#define val_t u32
#define sval_t u64
#endif
#define rotate(num,bits) ({ typeof(num) x=num;\
x=(x>>bits)|(x<<((sizeof(x)*8)-bits));x;})
#define rndgen64 randuint64
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
//----linear collission count----------
#define countudiag() (sumL+sumR)
#include "Functions/info.h"
//--------mainloop------
void linearsolve(){
 A=0,B=0;cend=__rdtsc();
 size_t NL=log2index(N);
 u64 lc=0,lcmax=(N)/NL,minstage2=((NL+8)*(NL+8)),endsearch=(NL/2)*(NL/2);

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime());goto endl;/*presolved*/}
print("\nT:",mstime()," ms Collisions:",cur);fflush(stdout);
//--------Main loop-------------
#include "Functions/windowslide.h"
if(cur!=0){info();goto first;}

fin:;
print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
endl:; //end loop
fflush(stdout);}


#include "Functions/diags.h"

#include "Functions/solve.h"
#include "Functions/integrity.h"
#include "Functions/presolve.h"
#include "Functions/scramble.h"



int main(int argc,char**argv){
if(argc<2){syntax:;puts("Syntax:nq N [p|f|t|c|i] [filename|sep]\n N=Board size min=8 \n p [string]=printboard [separator] \n f=write result as file \nt=test presolved array\n i filename=load u32/u64 queen array filename\n num+s =scramble rows num times(N*num)\nc= additional checks for integrity(slow)");exit(1);}
int nosolve=(argc>=3 && strchr(argv[2],'t'));//(test function for integrity with presolved diagonals)
 N=atoi(argv[1]);if(N<MINBOARD)goto syntax;


int fileload= (argc>=4 && strchr(argv[2],'i'));//load file with
checkb=(argc>=3 && strchr(argv[2],'c'));//additional checks
int scram=(argc>=3 && strchr(argv[2],'s'));//scramble rows
//u32/u64 queen rows in sequence( queenrow 0-N) size N*4;

board=malloc(sizeof(val_t)*N);//queen row/cols(2^31-1 max)

if(!board){perror("Queen array size too large for malloc");exit(2);}
fflush(stdout);
diagL=malloc(sizeof(val_t)*(N+2)*2);
diagR=malloc(sizeof(val_t)*(N+2)*2);
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}
if(!nosolve){//fixed order file or
if(fileload){fileloadfrom(argv[3]);
}else{//diagonal order queens
for(size_t i=0;i<N;i++){board[i]=i;}}
}else{ setpresolved();}

if(scram){size_t scrnum=atoi(argv[2]);scramble(scrnum);}
//for(size_t i=0;i<N;i++)board[i]=N-i-1;//r-diagonal
solve();
//verify no collisions (diagonals contain Q=1)
size_t verify=0;
for(size_t i=0;i<N;i++){
verify+=(diagL[board[i]+i])!=1;
verify+=(diagR[board[i]+(N-i)])!=1;}
//halt on error(stops nqtest.sh)
if(verify){print("Invalid solution to N=",N,"Collisions:",verify);fflush(stdout);char __attribute__((unused))  tt=getchar();exit(89);}
if(checkb){integrity();}
if((argc>=3 && strchr(argv[2],'p'))){
char* sep=argc>3?argv[3]:"\n";
printboard(sep);return 250;}
if((argc>=3 && strchr(argv[2],'f'))){fileboard();}
return 0;}
