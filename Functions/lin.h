//----------------Stage 3--------
void NOINLINE linearsolveend(){if(!cur)return;
esecond:;B=(rndedgecell(A));
emidloop:;verbinfo("EMidloop:");//midloop
swapc(A,B);incswap();
info("ESwap:");//fail==0 -> goodswap
if(unlikely(cur==0)){return;}
//next iteration:
if(unlikely(zerocols2(A))){goto eresetA;;}
goto esecond;
eresetA:;A=fstgcols(A);goto emidloop;

}

//--------------------Stage2---------------
void NOINLINE linearsolve(){if(!cur)return;
goto resetA;midloop:;verbinfo("Midloop:");
swapc(A,B);//badswap rejected at swapc.h
//goodswap:
goodswap:;incswap();
info("Swap:");best=cur;//new record
if(unlikely(cur<Blim))return linearsolveend();
if(zerocols2(A)){
resetA:;A=fstgcols(A);goto midloop;}
B=fstgcols(B);goto midloop;
}
