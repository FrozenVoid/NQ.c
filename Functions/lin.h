//--------mainloop------
void linearsolve(){
 A=0,B=0;cend=__rdtsc();
 size_t NL=log2index(N);
 u64 lc=0,lcmax=(N)/NL,minstage2=N<10000?1000000:((NL)*(NL)),endsearch=(NL/2)*(NL/2);

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"\n");goto endl;/*presolved*/}
print("\nT:",mstime()," ms Collisions:",cur,"\n");fflush(stdout);
//--------Main loop-------------
#include "windowslide.h"
if(cur!=0){info();goto first;}

fin:;
print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
endl:; //end loop
fflush(stdout);}
