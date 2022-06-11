//----------------main solver func--------


void linearsolveend(){if(!cur)return;
esecond:;B=(rndedgecell(A));
if(unlikely(fail>=failmax))goto eresetA;
emidloop:;
verbinfo("EMidloop:");//midloop
swapc(A,B);cur=countudiag();
if(unlikely(cur<best))goto egoodswap;
fail++;incfails();swapc(A,B);
verbinfo("EFail:");//fail test
goto esecond;egoodswap:;
incswap();fail=0;
info("ESwap:");//fail==0 -> goodswap
best=cur;//new record
if(unlikely(cur==0)){return;}
//next iteration:
if(likely(zerocols2(A))){goto eresetA;;}

goto esecond;
eresetA:;
A=fstgcols(A);
goto emidloop;

}

//pre Blim func
void linearsolve(){if(!cur)return;
A=fstgcols(A);second:;B=fstgcols(B);
if(unlikely(fail>=failmax))goto resetA;
verbinfo("Midloop:");//midloop
midloop:;
swapc(A,B);cur=countudiag();
if(unlikely(cur<=best)){goto goodswap;}
fail++;incfails();swapc(A,B);
verbinfo("Fail:");//fail test
goto second;goodswap:;
incswap();fail=0;
info("Swap:");//fail==0 -> goodswap
best=cur;//new record
if(unlikely(cur<Blim))return linearsolveend();
//next iteration:
if(zerocols2(A)){goto resetA;}

goto second;
resetA:;A=fstgcols(A);
goto midloop;
}
