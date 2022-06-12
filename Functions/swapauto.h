static inline void swapauto(val_t x,val_t y){
 if(unlikely(x==y))return;
 size_t prev=cur;
 swapreset:;
swapc(x,y);
if(cur>prev ){verbinfo("SwapReset");
fail++;incfails();decswap() ;

goto swapreset;}

incswap() ;//increment swaps(-1+1=0)

}
