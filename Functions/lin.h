//----------------main solver func--------


void linearsolveend(){if(!cur)return;
esecond:;B=(rndedgecell(A));
verbinfo("EMidloop:");//midloop
swapc(A,B);cur=countudiag();
if(unlikely(cur<best)||fail>failmax)goto egoodswap;
fail++;incfails();swapc(A,B);
verbinfo("EFail:");//fail test
goto esecond;egoodswap:;
incswap();fail=0;
info("ESwap:");//fail==0 -> goodswap
best=cur;//new record
if(unlikely(cur==0)){return;}
//next iteration:
if(unlikely(fail>=failmax)||likely(zerocols2(A))){A=fstgcols(A);;}

goto esecond;

}

//pre Blim func
void linearsolve(){if(!cur)return;
A=fstgcols(A);second:;
if(unlikely(cur<Blim))return linearsolveend();
B=fstgcols(B);
nextt:;
verbinfo("Midloop:");//midloop
swapc(A,B);cur=countudiag();
if(likely(cur>best))goto nfail;
incswap();fail=0;
info("Swap:");//fail==0 -> goodswap
best=cur;//new record
if(unlikely(cur==0)){return;}
//next iteration:
if(unlikely(fail>=failmax)||zerocols2(A)){A=fstgcols(A);;}

goto second;


nfail://new fail
fail++;incfails();swapc(A,B);
verbinfo("Fail:");//fail test
goto second;

}
