static inline const size_t rndedgecell(size_t X) {size_t startX=X*(X+edge<N);return startX+modreduce(N-startX);}
void NOINLINE edgecellsolver(){
const size_t edgefailmax=N<100?20:NL*NL*NL*17;
if(!cur)return;
print("\nStage3:",mstime(),"ms failmax:",edgefailmax,"\n");
esecond:;B=rndedgecell(A);
emidloop:;verbinfo("EMidloop:");//midloop
swapauto(A,B);//cur update in swapc()
info("ESwap:");
if(unlikely(cur==0)){return;}
best=cur;//new record
if(unlikely(zerocols2(A))||fail>edgefailmax){fail*=fail<edgefailmax;goto eresetA;;}
goto esecond;//next iteration:
eresetA:;A=fstgcols(A);goto emidloop;


}
