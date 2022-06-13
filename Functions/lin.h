
//--------------------Stage2---------------
void NOINLINE linearsolve(){
const size_t stage3lim=119+N/512;
const size_t failmax=NL*NL;
void*nextB=&&resetBfst;
void* skip=&&skip1;
if(!cur)return;
print("\nStage2: ",mstime(),"ms Stage3Lim:",stage3lim,"cols\n");
goto resetA;midloop:;verbinfo("Midloop:");
swapauto(A,B);//badswap rejected
info("Swap:");best=cur;//new record
//exit check
if(unlikely(!cur))return;
goto *skip;
skip1:;
if(unlikely(cur<stage3lim)){nextB=&&resetBrnd;skip=&&skip2;}
//A refresh
skip2:;
if(unlikely(zerocols2(A))||fail>failmax){verbinfo("ResetA");
fail=0;
resetA:;A=fstgcols(A);goto midloop;}

goto *nextB;
//next swap
resetBrnd:B=rndedgecell(A);goto midloop;
resetBfst:B=fstgcols(B);goto midloop;
}
