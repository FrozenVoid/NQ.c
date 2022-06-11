void NOINLINE edgecellsolver(){if(!cur)return;
//failmax;
print("\nStage3:",mstime(),"ms\n");
esecond:;B=rndcell();
emidloop:;verbinfo("EMidloop:");//midloop
swapc(A,B);//cur update in swapc()
if(unlikely(cur<best))goto egoodswap;
fail++;
incfails();
verbinfo("EFail:");//fail test
if(unlikely(fail>=failmax)){fail=0;best=cur;goto eresetA;}
goto swapfix;egoodswap:;
incswap();fail=0;info("ESwap:");
if(unlikely(cur==0)){return;}
best=cur;//new record
if(unlikely(zerocols2(A))){goto eresetA;;}
goto esecond;//next iteration:
eresetA:;A=fstgcols(A);goto emidloop;
swapfix:;swapc(A,B); goto esecond;

}
