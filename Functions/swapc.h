 static inline void swapdiag(val_t x,val_t y){
i64  clx,crx,cly,cry;
tswaps++;swaps+=dir;//valid swaps total
//prefetch at rndcell()
clx=diagL[board[x]+x]--;//current X pos Left
cly=diagL[board[y]+y]--;//current y pos Left
crx=diagR[board[x]+(N-x)]--;
cry=diagR[board[y]+(N-y)]--;
//clear/set occupied diagonals(none==1)

bitset_set_to_value(bitdiagL,board[x]+x,!diagL[board[x]+x]);
bitset_set_to_value(bitdiagL,board[y]+y,!diagL[board[y]+y]);
bitset_set_to_value(bitdiagR,board[x]+(N-x),!diagR[board[x]+(N-x)]);
bitset_set_to_value(bitdiagR,board[y]+(N-y),!diagR[board[y]+(N-y)]);

//reduce sums,first,last
//if clx==1 0 clx>1=1  (clx-1)=0
sumL-=!!(clx-1);//reduce sum if old collision
sumL-=!!(cly-1);
sumR-=!!(crx-1);
sumR-=!!(cry-1);

//swap
swapq(x,y);
//updates sums
clx=(++diagL[board[x]+x]);
cly=(++diagL[board[y]+y]);;
crx=(++diagR[board[x]+(N-x)]);
cry=(++diagR[board[y]+(N-y)]);

//clear/set occupied diagonals(none==1)

bitset_set_to_value(bitdiagL,board[x]+x,!diagL[board[x]+x]);
bitset_set_to_value(bitdiagL,board[y]+y,!diagL[board[y]+y]);
bitset_set_to_value(bitdiagR,board[x]+(N-x),!diagR[board[x]+(N-x)]);
bitset_set_to_value(bitdiagR,board[y]+(N-y),!diagR[board[y]+(N-y)]);

sumL+=!!(clx-1);//reduce sum if old collision
sumL+=!!(cly-1);
sumR+=!!(crx-1);
sumR+=!!(cry-1);

}


 static inline void swapc(val_t x,val_t y){
i64  clx,crx,cly,cry;
tswaps++;swaps+=dir;//valid swaps total
//prefetch at rndcell()
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
swapq(x,y);
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
