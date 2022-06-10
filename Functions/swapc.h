
 static inline void swapc(val_t x,val_t y){
 if(unlikely(x==y))return;
i64  clx,crx,cly,cry;
#ifndef SILENCE
tswaps++;// swaps total(all)
#endif
//prefetch at rndcell()
clx=diagL[board[x]+x]--;//current X pos Left
cly=diagL[board[y]+y]--;//current y pos Left
crx=diagR[board[x]+(N-x)]--;
cry=diagR[board[y]+(N-y)]--;

//reduce sums,first,last
//if clx==1 0 clx>1=1  (clx-1)=0
if(unlikely((clx-1)))sumL--;
if(unlikely((crx-1)))sumR--;
if(unlikely((cly-1)))sumL--;
if(unlikely((cry-1)))sumR--;
//swap
swapq(x,y);

//updates sums
clx=(++diagL[board[x]+x]);
cly=(++diagL[board[y]+y]);;
crx=(++diagR[board[x]+(N-x)]);
cry=(++diagR[board[y]+(N-y)]);
//0 1+
if(unlikely((clx-1)))sumL++;
if(unlikely((crx-1)))sumR++;
if(unlikely((cly-1)))sumL++;
if(unlikely((cry-1)))sumR++;


}
