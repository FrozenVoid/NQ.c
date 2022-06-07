//======prefill counts and start solver===
void solve(void){
//fill queen location counts
//set occupied diagonals to 0
for(size_t i=0;i<N;i++){diagL[board[i]+i]++;
bitset_set_to_value(bitdiagL,board[i]+i,0);
}
for(size_t i=0;i<N;i++){diagR[board[i]+(N-i)]++;
bitset_set_to_value(bitdiagR,board[i]+(N-i),0);
}

//calculate Sums of collisions
for(size_t i=0;i<N*2;i++){sumL+=(diagL[i]-1)*(diagL[i]>1);}
for(size_t i=0;i<N*2;i++){sumR+=(diagR[i]-1)*(diagR[i]>1);}
linearsolve();}
