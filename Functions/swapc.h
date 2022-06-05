void swapc(val_t x,val_t y){
val_t  clx,crx,cly,cry;
tswaps++;swaps+=dir;//valid swaps total
FETC(&diagL[board[x]+x],1,0);
FETC(&diagL[board[y]+y],1,0);
FETC(&diagR[board[x]+(N-x)],1,0);
FETC(&diagR[board[y]+(N-y)],1,0);
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
FETC(&diagL[board[x]+x],1,0);
FETC(&diagL[board[y]+y],1,0);
FETC(&diagR[board[x]+(N-x)],1,0);
FETC(&diagR[board[y]+(N-y)],1,0);
clx=(++diagL[board[x]+x]);
cly=(++diagL[board[y]+y]);;
crx=(++diagR[board[x]+(N-x)]);
cry=(++diagR[board[y]+(N-y)]);

sumL+=!!(clx-1);//reduce sum if old collision
sumL+=!!(cly-1);
sumR+=!!(crx-1);
sumR+=!!(cry-1);

}
