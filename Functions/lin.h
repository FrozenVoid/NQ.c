
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
