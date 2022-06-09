//----------------main solver func--------
void linearsolve(){A=fstgcols(A);
second:;
///do(fstgcols) while(A==B) prevents infinite loop
if(unlikely(cur<Blim))B=rndcell();else{
fstB:;B=fstgcols(B);
if(unlikely(A==B))goto fstB;}
//A==B allowed if cur<Blim(to failmax)
verbinfo("Midloop:");//midloop
swapc(A,B);cur=countudiag();
if(unlikely(cur>best)){
fail++;incfails();swapc(A,B);
verbinfo("Fail:");//fail test
goto second;}
incswap();fail=cur>=best?fail:0;
info("Swap:");//fail==0 -> goodswap
best=cur;//new record
if(unlikely(cur==0)){return;}
//next iteration:
if((fail>=failmax)||zerocols(A))A=fstgcols(A);
fail=0;goto second;
}
