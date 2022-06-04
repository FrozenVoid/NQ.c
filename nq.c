#include "Util/void.h"//https://github.com/FrozenVoid/C-headers
//linear ~O(N) NQueens  solver

#define NCYCLES 8 //report each NCYCLES
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#define tsctime(c) ((__rdtsc()-c)>>30)
#define QDEBUG 1//print debug/iteration data
#define val_t u32
#define rotate(num,bits) ({ typeof(num) x=num;\
x=(x>>bits)|(x<<((sizeof(x)*8)-bits));x;})
#define rndgen64 randuint64
#define rndgen32 msws

//from https://arxiv.org/abs/1704.00358
static uint32_t msws() {
static uint64_t x = 266346241, w = 0, s = 0xb5ad4eceda1ce2a9;
   x *= x; x += (w += s); return x = (x>>32) | (x<<32);}





val_t N,A=0,B=1;
val_t * board;
val_t * diagL;i64 sumL=0;
val_t * diagR;i64 sumR=0;
i64 swapt=0,swaps=0,checkb=0;//valid swaps total(set if QDEBUG enabled)
size_t loops=0,fail=0,tfail=0,dir=1,tswaps=0,cend,valr,cur,best;

#define swapq(x,y) ({val_t temp=x;x=y;y=temp;})

 void swapc(val_t x,val_t y){
val_t  clx,crx,cly,cry;
#if QDEBUG
tswaps++;swaps+=dir;//valid swaps total
#endif
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
 val_t qccount(u32 P){
//cannot be zero due being set from q[]
val_t s=board[P];
return ((diagL[s+P]))+((diagR[s+(N-P)]))-2;}
int zerocols(u32 P){//1= no collision,0==has cols
const val_t s=board[P];
return ((diagL[s+P])==1)&((diagR[s+(N-P)])==1);
}

 val_t qccount2(u32 P,u32 P2){
//cannot be zero due being set from q[]
val_t s=board[P],s2=board[P2];
return ((diagL[s+P]))+((diagR[s+(N-P)]))+ ((diagL[s2+P2]))+((diagR[s2+(N-P2)]))-4;}

val_t fstcols(){
for(size_t i=0;i<N;i++){if(qccount(i))return i;};return N;}

val_t fstgcols(val_t G){//first greater then
for(size_t i=G+1;i<N;i++){if(qccount(i))return i;};return N;}
//--------------------------
void printboard(char* sep){print("\n");for(size_t i=0;i<N-1;i++)print(board[i]+1,sep);print(board[N-1],"\n");}

void fileboard(){char* fname=malloc(126);
sprintf(fname,"%u.nq",N);
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
size_t vfqsize=fread(board,4,N,in);
if(vfqsize!=N){ print("File:",name,"reading failed at  queen#",vfqsize);perror("");exit(112);}
print("Loaded:",name," N=",N);
fclose(in);
}


//https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/

 val_t modreduce(uint32_t x, uint32_t N) {
  return ((uint64_t) x * (uint64_t) N) >> 32 ;
}
val_t rndcell(){return modreduce(rndgen32(),N);}
//-----------linear collission count----------
#define countudiag() (sumL+sumR)
//------------------------
 void info(){
  if(tsctime(cend)>NCYCLES ){
  clock_t Ntime=mstime();
  print("\n cols=",cur,"A=",A,"valid/fail:",swaps,"/",(fail),"\nswap:",1.0*swapt/Ntime,"fail:",1.0*tfail/Ntime,"loops:",1.0*loops/Ntime);
  print("\nT:",Ntime,"ms Col%",100.0*(cur)/N,"Swapt",swapt,"Valid%",100.0*swapt/tswaps);cend=__rdtsc();fflush(stdout);}}
//--------------------------------------------
void linearsolve(){
 A=0,B=0;
 //large board speedup
 val_t minsearch=N>10000?log2index(N)/2:0,endsearch=minsearch*minsearch;
cend=__rdtsc();u64 lc=0,lcmax=(N/4)/log2index(N);
 cur=countudiag(),best=cur;if(cur==0){;goto endl;/*presolved*/}
 if(cur<minsearch)goto endsearch;
#if QDEBUG
print("\nT:",mstime()," ms Collisions:",cur," SearchLim:",minsearch);fflush(stdout);
#endif
//--------Main loop-------------
loop:;
#if QDEBUG
loops++;
#endif
do{A=rndcell();}while(zerocols(A));
loop2:;lc=0;
do{B=rndcell(); lc++;}while( zerocols(B) & (lc<lcmax) );

//-------begin swap-----------
#if QDEBUG
dir=1;
#endif
swapc(A,B);cur=countudiag();//count diagonal intersects
//----bad swap-----
if(cur>best){
#if QDEBUG
dir=-1;fail++;
#endif
swapc(A,B);
goto loop2;}
 if(cur==best){;goto loop;}
//-----good swap------
#if QDEBUG
tfail+=fail;swapt+=swaps;
info();//new iteration update
fail=0;;swaps=0;
#endif
best=cur;
//=================Search at ending========================

endsearch:;
if( best<minsearch ){//ending speedup for N > L2 cache
#if QDEBUG
print("\nEnd search:",mstime()," ms Collisions:",best);fflush(stdout);
#endif
innerloop:;
B=fstcols();

innerloop2:;lc=0;
if(cur>1){A=fstgcols(A>B?A:B);if(A==N)goto skip;}else{skip:;
do{A=rndcell();lc++;}while(!qccount(A) & ( 	lc<endsearch) );
if(A==B)goto innerloop2;}

#if QDEBUG
dir=1;
#endif
swapc(A,B);cur=countudiag();
if(cur==0){goto endl;}
if(cur<=best){
#if QDEBUG
fail=0;if(cur<best)info();
#endif
best=cur;goto innerloop;}
#if QDEBUG
dir=-1;fail++;
#endif
swapc(A,B);goto innerloop2;

}


if(cur>0){goto loop;;}
//-----------Success-----
endl:; //end loop
#if QDEBUG
 print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");fflush(stdout);
#endif
}

size_t diags(u32*board,size_t len){//first collision
for(size_t i=0;i<len;i++){size_t cur=board[i];
#if QDEBUG
if(!(i&0xff)){putchar('+');fflush(stdout);}
#endif
 for(size_t z=i+1;z<len;z++){
  size_t zqueen=board[z];
 if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){return i; };   }  }
return 0;}
//===================Solver===========================
void solve(void){
//fill queen location counts
for(size_t i=0;i<N;i++){diagL[board[i]+i]++;}
for(size_t i=0;i<N;i++){diagR[board[i]+(N-i)]++;}
//calculate Sums of collisions

for(size_t i=0;i<N*2;i++){sumL+=(diagL[i]-1)*(diagL[i]>1);}
for(size_t i=0;i<N*2;i++){sumR+=(diagR[i]-1)*(diagR[i]>1);}
linearsolve();



}

void integrity(){
//pedantic checks
char __attribute__((unused))  tt2;
if(sumL+sumR){print("\nInvalid sumL+sumR to N=",N,"Collisions:",sumL+sumR);fflush(stdout); tt2=getchar();exit(31);}else{
if(N>100000){print("\nWarning:",N," >100000 slow checks");}
size_t fdg=diags(board,N);
if(fdg){print("\nUnsolved collision at column:",fdg,"/",N,"Reported Collisions:",sumL+sumR);fflush(stdout); tt2=getchar();exit(32);}
} print("\nAll checks passed!\n");
}
void setpresolved(){
if(N%6<2||N%6>=4){// presolved: place knight diagonals
for(size_t i=0,z=1;i<N;i++,z+=2){
if(z>=N){z=0;}board[i]=z;;}
}else if(N%6==2){
for(size_t i=0,z=1;z<N;i++,z+=2){board[i]=z;}
for(size_t i=N/2,z=2;z &&i<N;i++,z-=2){board[i]=z;}
for(size_t i=2+N/2,z=6;z<N-1 &&i<N;i++,z+=2){board[i]=z;}
board[N-1]=4;
}else if(N%6==3){size_t c9,z;

for(c9=0,z=3;z<N-1;c9++,z+=2){board[c9]=z;}
board[c9++]=1;
for(z=4;c9<N-2;c9++,z+=2){board[c9]=z;}
board[c9++]=0;board[c9++]=2;
}}

void scramble(size_t num){
 print("\nScrambling N=",N," Times:",num,"\n");fflush(stdout);

for(size_t z=0;z<num;z++){
for(size_t i=0;i<N;i++){swapq(board[i],board[rndcell()]);}
}}
int main(int argc,char**argv){
if(argc<2){syntax:;puts("Syntax:nq N [p|f|t|c|i] [filename|sep]\n N=Board size min=8 \n p [string]=printboard [separator] \n f=write result as file \nt=test presolved array\n i filename=load u32 queen array filename\n num+s =scramble rows num times(N*num)\nc= additional checks for integrity(slow)");exit(1);}
int nosolve=(argc>=3 && strchr(argv[2],'t'));//(test function for integrity with presolved diagonals)
 N=atoi(argv[1]);if(N<8)goto syntax;
int fileload= (argc>=4 && strchr(argv[2],'i'));//load file with
checkb=(argc>=3 && strchr(argv[2],'c'));//additional checks
int scram=(argc>=3 && strchr(argv[2],'s'));//scramble rows
//u32 queen rows in sequence( queenrow 0-N) size N*4;

board=malloc(sizeof(val_t)*N);//queen row/cols(2^31-1 max)

if(!board){perror("Queen array size too large for malloc");exit(2);}
fflush(stdout);
diagL=malloc(sizeof(val_t)*(N+2)*2);
diagR=malloc(sizeof(val_t)*(N+2)*2);
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}
if(!nosolve){
if(fileload){fileloadfrom(argv[3]);
}else{//normal order queens
for(size_t i=0;i<N;i++){board[i]=i;}}
}else{ setpresolved();}

if(scram){size_t scrnum=atoi(argv[2]);scramble(scrnum);}
//for(size_t i=0;i<N;i++)board[i]=N-i-1;//r-diagonal
solve();
//verify no collisions (diagonals contain Q=1)
size_t verify=0;
for(size_t i=0;i<N;i++){
verify+=(diagL[board[i]+i])!=1;
verify+=(diagR[board[i]+(N-i)])!=1;
}
//halt on error(stops nqtest.sh)
if(verify){print("Invalid solution to N=",N,"Collisions:",verify);fflush(stdout);char __attribute__((unused))  tt=getchar();exit(89);}
if(checkb){integrity();}

if((argc>=3 && strchr(argv[2],'p'))){
char* sep=argc>3?argv[3]:"\n";
printboard(sep);return 250;}

if((argc>=3 && strchr(argv[2],'f'))){fileboard();}

return 0;}
