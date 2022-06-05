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

 static inline void swapc(val_t x,val_t y){
val_t  clx,crx,cly,cry;
tswaps++;swaps+=dir;//valid swaps total
FETC(&diagL[board[x]+x],1,0);
FETC(&diagL[board[y]+y],1,0);
FETC(&diagR[board[x]+(N-x)],1,0);
FETC(&diagR[board[y]+(N-y)],1,0);
clx=diagL[board[x]+x]--;//current X pos Left
cly=diagL[board[y]+y]--;//current y pos Left
crx=diagR[board[x]+(N-x)]--;
cry=diagR[board[y]+(N-y)]--;
//reduce sums,first,last
//if clx==1 0 clx>1=1  (clx-1)=0
sumL-=!!(clx-1);//reduce sum if old collision
sumL-=!!(cly-1);
sumR-=!!(crx-1);
sumR-=!!(cry-1);
//swap
swapq(board[x],board[y]);
//updates sums
FETC(&diagL[board[x]+x],1,0);
FETC(&diagL[board[y]+y],1,0);
FETC(&diagR[board[x]+(N-x)],1,0);
FETC(&diagR[board[y]+(N-y)],1,0);
clx=(++diagL[board[x]+x]);
cly=(++diagL[board[y]+y]);;
crx=(++diagR[board[x]+(N-x)]);
cry=(++diagR[board[y]+(N-y)]);

sumL+=!!(clx-1);//reduce sum if old collision
sumL+=!!(cly-1);
sumR+=!!(crx-1);
sumR+=!!(cry-1);

}


//queen collisons at position: 2=none,2+=collision
static inline val_t qccount(val_t P){
//cannot be zero due being set from q[]
FETC(&board[P],0,0);
val_t s=board[P];
FETC(&diagL[s+P],0,0);
FETC(&diagR[s+(N-P)],0,0);
return ((diagL[s+P]))+((diagR[s+(N-P)]))-2;}
static inline int zerocols(val_t P){//1= no collision,>1 collisions


FETC(&board[P],0,0);
const val_t s=board[P];
FETC(&diagL[s+P],0,0);
if((diagL[s+P])!=1)return 0;
FETC(&diagR[s+(N-P)],0,0);
if(diagR[s+(N-P)]!=1)return 0;
return 1;
//return !((((diagL[s+P])) +(diagR[s+(N-P)]))-2);//1:1=
//return !((((diagL[s+P]))+((diagR[s+(N-P)])))-2);
}


static inline val_t fstcols(){
for(size_t i=0;i<N;i++){if(qccount(i))return i;};return N-1;}

static inline val_t fstgcols(val_t G){//first greater then
for(size_t i=G+1;i<N;i++){
if(qccount(i))return i;};return fstcols();}
//--------------------------
void printboard(char* sep){print("\n");for(size_t i=0;i<N-1;i++)print(board[i]+1,sep);print(board[N-1],"\n");}

void fileboard(){char* fname=malloc(126);
sprintf(fname,"%"PRIu64".nq",(u64)N);
FILE*out=fopen(fname,"wb");
print("\nWriting board into",fname);
size_t rfwout=fwrite(board,4,N,out);
if(rfwout==N){print("\nFile:",fname,"\nRecorded board as file\n");}
else{print("\nFile:",fname,"\nWrite mismatch\n",N,"!=",rfwout);}
fclose(out);
}

void fileloadfrom(char* name){
FILE* in=fopen(name,"rb");
if(!in){print("File:",name," cannot be opened");perror("");exit(111);}
size_t vfqsize=fread(board,sizeof(val_t),N,in);
if(vfqsize!=N){ print("File:",name,"reading failed at  queen#",vfqsize);perror("");exit(112);}
print("Loaded ",sizeof(val_t),"byte NQ file:",name," N=",N);
fclose(in);}

//https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/
 static inline val_t modreduce(val_t x, val_t N) {
return ((sval_t) x * (sval_t) N) >> (sizeof(val_t)*8);}

 static inline val_t rndcell(){
 val_t r=modreduce((val_t)randuint64(),N);
 FETC(&board[r],0,0);
 return r;
 }
//----linear collission count----------
#define countudiag() (sumL+sumR)
//------------------------
#ifdef SILENCE
#define info()
#else
 void info(){
  if(__rdtsc()-cend>NCYCLES  ){
  clock_t Ntime=mstime();
  print("\n cols=",best,"A=",A,"B=",B,"valid/fail:",swaps,"/",(fail),"\nswap:",1.0*swapt/Ntime,"fail:",1.0*tfail/Ntime);
  print("\nT:",Ntime,"ms Col%",100.0*(cur)/N,"Swapt",swapt,"Valid%",100.0*swapt/tswaps);cend=__rdtsc();fflush(stdout);}}
#endif
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

size_t diags(val_t*board,size_t len){//first collision
for(size_t i=0;i<len;i++){size_t cur=board[i];
if(!(i&0xfff)){putchar('+');fflush(stdout);}
 for(size_t z=i+1;z<len;z++){
  size_t zqueen=board[z];
 if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){return i; };   }  }
return 0;}


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
