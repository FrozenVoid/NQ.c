void NOINLINE linearsolveend(){if(!cur)return;
verbprint("Stage3:",mstime(),"ms\n");
esecond:;B=(rndedgecell(A));
emidloop:;
verbinfo("EMidloop:");//midloop
swapc(A,B);
if(unlikely(cur<best))goto egoodswap;
fail++;incfails();verbinfo("EFail:");//fail test
if(unlikely(fail>=failmax)){fail=0;best=cur;goto eresetA;}
goto swapfix;egoodswap:;
incswap();fail=0;
info("ESwap:");//fail==0 -> goodswap
best=cur;//new record
if(unlikely(cur==0)){return;}
//next iteration:
if(unlikely(zerocols2(A))){goto eresetA;;}

goto esecond;
eresetA:;A=fstgcols(A);goto emidloop;
swapfix:;swapc(A,B); goto esecond;

}
//--------------------Stage2---------------
void NOINLINE linearsolve(){if(!cur)return;
verbprint("Stage2:",mstime(),"ms\n");
goto resetA;midloop:;verbinfo("Midloop:");
if(unlikely(cur<Blim))return linearsolveend();
swapauto(A,B);//badswap rejected at swapc.h
//goodswap:
goodswap:;incswap();
info("Swap:");best=cur;//new record

if(zerocols2(A)){verbinfo("ResetA");
resetA:;A=fstgcols(A);goto midloop;}
B=fstgcols(B);goto midloop;
}
