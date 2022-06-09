//======prefill counts and start solver===
void solve(void){
//fill queen location counts
for(size_t i=0;i<N;i++){diagL[board[i]+i]++;}
for(size_t i=0;i<N;i++){diagR[board[i]+(N-i)]++;}

//calculate Sums of collisions
for(size_t i=0;i<N*2;i++){sumL+=(diagL[i]-1)*(diagL[i]>1);}
for(size_t i=0;i<N*2;i++){sumR+=(diagR[i]-1)*(diagR[i]>1);}

 cend=__rdtsc();
 NL=log2index(N);
  failmax=160+NL;edge=N/64+128;
  Blim=9+NL*NL*NL*NL;

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"ms\n");goto endl;/*presolved*/}
print("\nSTART:",mstime()," ms Collisions:",cur,"Blim:",Blim,"failmax:",failmax,"edge:",edge,"\n");fflush(stdout);

fastdiagswap();
clock_t linear_begin=mstime();
verbprint("Linear:",linear_begin,"ms\n");
linearsolve();//main func
clock_t linear_end=mstime()-linear_begin;
#ifndef SILENCE
print("\nSolved N=",N," in",linear_end,"ms(linear solver only)\n Swaps:",swapt,"Fails:",tfail,"\n");
#else
print("\nSolved N=",N," in ",linear_end,"ms(linear solver only)\n");
#endif
endl:;fflush(stdout);
}
