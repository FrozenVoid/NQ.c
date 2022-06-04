#include "Util/void.h"//https://github.com/FrozenVoid/C-headers
//linear ~O(N) NQueens  solver

size_t NCYCLES=8; //report each NCYCLES
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#define tsctime(c) ((__rdtsc()-c)>>30)
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
size_t loops=0,fail=0,tfail=0,dir=1,tswaps=0,cend,valr,cur,best;

#define swapq(x,y) ({val_t temp=x;x=y;y=temp;})

 static inline void swapc(val_t x,val_t y){
val_t  clx,crx,cly,cry;
tswaps++;swaps+=dir;//valid swaps total
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
static inline val_t qccount(val_t P){
//cannot be zero due being set from q[]
val_t s=board[P];
return ((diagL[s+P]))+((diagR[s+(N-P)]))-2;}
static inline int zerocols(val_t P){//1= no collision,0==has cols
const val_t s=board[P];
return ((diagL[s+P])==1)&((diagR[s+(N-P)])==1);
}

  static inline val_t qccount2(val_t P,val_t P2){
//cannot be zero due being set from q[]
val_t s=board[P],s2=board[P2];
return ((diagL[s+P]))+((diagR[s+(N-P)]))+ ((diagL[s2+P2]))+((diagR[s2+(N-P2)]))-4;}

static inline val_t fstcols(){
for(size_t i=0;i<N;i++){if(qccount(i))return i;};return N;}

static inline val_t fstgcols(val_t G){//first greater then
for(size_t i=G+1;i<N;i++){if(qccount(i))return i;};return N;}
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

 static inline val_t rndcell(){ return
  modreduce((val_t)randuint64(),N);
 }
//----linear collission count----------
#define countudiag() (sumL+sumR)
//------------------------
 void info(){
  if(tsctime(cend)>NCYCLES ){
  clock_t Ntime=mstime();
  print("\n cols=",cur,"A=",A,"valid/fail:",swaps,"/",(fail),"\nswap:",1.0*swapt/Ntime,"fail:",1.0*tfail/Ntime,"loops:",1.0*loops/Ntime);
  print("\nT:",Ntime,"ms Col%",100.0*(cur)/N,"Swapt",swapt,"Valid%",100.0*swapt/tswaps,"lcmax:",valr);cend=__rdtsc();fflush(stdout);}}
//--------mainloop------
void linearsolve(){
 A=0,B=0;cend=__rdtsc();u64 lc=0,lcmax=(N*4)/log2index(N);
 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime());goto endl;/*presolved*/}
print("\nT:",mstime()," ms Collisions:",cur);fflush(stdout);
//--------Main loop-------------
loop:;loops++;
do{A=rndcell();}while(zerocols(A));
loop2:;lc=0;
do{B=rndcell(); lc++;}while( zerocols(B) & (lc<lcmax) );
valr+=lc==lcmax;
//-------begin swap-----------
dir=1;swapc(A,B);cur=countudiag();
//----bad swap-----
if(cur>best){dir=-1;fail++;
swapc(A,B);goto loop2;}
tfail+=fail;swapt+=swaps;
info();//new iteration update
fail=0;;swaps=0;best=cur;//new record
if(cur>0){goto loop;;}
//-----------Success-----

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
//======prefill counts and start solver===
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
if(argc<2){syntax:;puts("Syntax:nq N [p|f|t|c|i] [filename|sep]\n N=Board size min=8 \n p [string]=printboard [separator] \n f=write result as file \nt=test presolved array\n i filename=load u32/u64 queen array filename\n num+s =scramble rows num times(N*num)\nc= additional checks for integrity(slow)");exit(1);}
int nosolve=(argc>=3 && strchr(argv[2],'t'));//(test function for integrity with presolved diagonals)
 N=atoi(argv[1]);if(N<8)goto syntax;
 if(N<1024)NCYCLES=0;//show verbose info

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
