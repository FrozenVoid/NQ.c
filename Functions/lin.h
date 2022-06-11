//----------------Stage 3--------
void NOINLINE linearsolveend(){if(!cur)return;
esecond:;B=(rndedgecell(A));
emidloop:;
verbinfo("EMidloop:");//midloop
swapc(A,B);cur=countudiag();
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
goto resetA;second:;goto resetB;
failmaxjmp:;
if(unlikely(fail>failmax2))goto resetA;
verbinfo("Midloop:");//midloop
midloop:;
swapc(A,B);cur=countudiag();
if(unlikely(cur<=best)){goto goodswap;}
fail++;incfails();swapc(A,B);
verbinfo("Fail:");//fail test
resetB:;
B=fstgcols(B);goto failmaxjmp;goodswap:;
incswap();fail=0;
info("Swap:");//fail==0 -> goodswap
best=cur;//new record
if(unlikely(cur<Blim))return linearsolveend();
//next iteration:
if(zerocols2(A)){goto resetA;}

goto second;
resetA:;fail=0;A=fstgcols(A);
goto midloop;
}
