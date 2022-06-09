//----------------main solver func--------
void linearsolve(){A=fstgcols(A);
second:;
///do(fstgcols) while(A==B) prevents infinite loop
if(unlikely(cur<Blim))goto rndB;
fstB:;B=fstgcols(B);
if(unlikely(A==B))goto fstB;
nextt:;
verbinfo("Midloop:");//midloop
swapc(A,B);cur=countudiag();
if(unlikely(cur>best))goto nfail;
incswap();fail=cur>=best?fail:0;
info("Swap:");//fail==0 -> goodswap
best=cur;//new record
if(unlikely(cur==0)){return;}
//next iteration:
if(fail>=failmax||zerocols(A)){goto resetA;}
goto second;
//control flow: jumps are cheap.
rndB:;
B=rndcell();
goto nextt;
nfail://new fail
fail++;incfails();swapc(A,B);
verbinfo("Fail:");//fail test
goto second;
resetA:;//reset A
fail=0;A=fstgcols(A);
goto second;
}
