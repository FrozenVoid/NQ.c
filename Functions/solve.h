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
  lc=0,lcmax=2+((N)/(NL*NL)),failmax=160+((NL));
  Blim=8+NL*NL*NL;

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"ms\n");goto endl;/*presolved*/}
print("\nSTART:",mstime()," ms Collisions:",cur,"Blim:",Blim,"failmax:",failmax,"\n");fflush(stdout);

fastdiagswap();
#ifdef VERBOSE
print("Linear:",mstime(),"ms\n");
#endif
linearsolve();//main func
#ifndef SILENCE
print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
#else
print("\nSolved N=",N," at:",mstime(),"ms\n");
#endif
endl:;fflush(stdout);
}
