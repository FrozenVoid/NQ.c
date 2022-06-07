//======prefill counts and start solver===
void solve(void){
//fill queen location counts
for(size_t i=0;i<N;i++){diagL[board[i]+i]++;
if(diagL[board[i]+i]>1)asetbit(bitcols,i);
}
for(size_t i=0;i<N;i++){diagR[board[i]+(N-i)]++;
if(diagR[board[i]+(N-i)]>1)asetbit(bitcols,i);
}
//calculate Sums of collisions

for(size_t i=0;i<N*2;i++){sumL+=(diagL[i]-1)*(diagL[i]>1);}
for(size_t i=0;i<N*2;i++){sumR+=(diagR[i]-1)*(diagR[i]>1);}
linearsolve();}
