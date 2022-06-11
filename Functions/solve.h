
//======prefill counts and start solver===
void solve(void){
if(N==2||N==3){print("No solution for N=",N,"\n");exit(0);}
//fill queen location counts
verbprint("Filling diagonals: T:",mstime(),"ms\n");
for(size_t i=0;i<N;i++){diagL[board[i]+i]++;}
for(size_t i=0;i<N;i++){diagR[board[i]+(N-i)]++;}
verbprint("Summing diagonals: T:",mstime(),"ms\n");
//calculate Sums of collisions
for(size_t i=0;i<N*2;i++){sumL+=(diagL[i]-1)*(diagL[i]>1);}
for(size_t i=0;i<N*2;i++){sumR+=(diagR[i]-1)*(diagR[i]>1);}

 cend=__rdtsc();
 NL=log2index(N);
  failmax=N<100?20:NL*NL*NL*17;
  failmax2=N<100?10:NL*NL*NL;
  edge=N/64+128;
  Blim=119+N/512;


 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"ms\n");goto endl;/*presolved*/}


fastdiagswap();
print("\nSTART:",mstime()," ms Collisions:",cur,"Blim:",Blim,"failmax:",failmax,"edge:",edge,"\n");FLUSH;
clock_t linear_begin=mstime();
linearsolve();//main func
clock_t linear_end=mstime()-linear_begin;
#ifndef SILENCE
print("\nSolved N=",N," in",linear_end,"ms(linear solver only)\n Swaps:",swapt,"Fails:",tfail,"\n");
#else
print("\nSolved N=",N," in ",linear_end,"ms(linear solver only)\n");
#endif
endl:;FLUSH;
}

