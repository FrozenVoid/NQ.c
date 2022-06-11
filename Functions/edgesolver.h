void NOINLINE edgecellsolver(){
const size_t edgefailmax=N<100?20:NL*NL*NL*17;
if(!cur)return;
print("\nStage3:",mstime(),"ms failmax:",edgefailmax,"\n");
esecond:;B=rndedgecell(A);
emidloop:;verbinfo("EMidloop:");//midloop
swapc(A,B);//cur update in swapc()
if(unlikely(cur<best))goto egoodswap;
fail++;
incfails();verbinfo("EFail:");//fail test
if(unlikely(fail>=edgefailmax)){fail=0;best=cur;goto eresetA;}

goto swapfix;egoodswap:;
incswap();fail=0;info("ESwap:");
if(unlikely(cur==0)){return;}
best=cur;//new record
if(unlikely(zerocols2(A))){goto eresetA;;}
goto esecond;//next iteration:
eresetA:;A=fstgcols(A);goto emidloop;
swapfix:;swapc(A,B); goto esecond;

}
