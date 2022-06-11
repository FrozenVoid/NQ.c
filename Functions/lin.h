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
//--------------------Stage2---------------
void NOINLINE linearsolve(){
const val_t stage3lim=119+N/512;
if(!cur)return;
print("\nStage2: ",mstime(),"ms Stage3Lim:",stage3lim,"cols\n");
goto resetA;midloop:;verbinfo("Midloop:");

swapauto(A,B);//badswap rejected at swapc.h

//goodswap:
goodswap:;
info("Swap:");best=cur;//new record
//exit check
//if(unlikely(!cur))return;
if(unlikely(cur<stage3lim))return edgecellsolver();
//A refresh
if(unlikely(zerocols2(A))){verbinfo("ResetA");
resetA:;A=fstgcols(A);goto midloop;}
//next swap
B=fstgcols(B);goto midloop;
}
