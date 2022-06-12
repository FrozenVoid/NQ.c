static inline void swapauto(val_t x,val_t y){
if(unlikely(x==y))return;
 size_t prev=cur;
 swapreset:;
val_t clx,crx,cly,cry;//current:right/left:x/y
#ifndef SILENCE
tswaps++;// swaps total(all)
#endif

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

cur=sumL+sumR;
if(cur>prev ){verbinfo("SwapReset");
fail++;incfails();decswap() ;

goto swapreset;}

incswap() ;//increment swaps(-1+1=0)

}
