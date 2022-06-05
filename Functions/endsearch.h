void esearch(){
//print("\n\n\n\n\n\n\n\n\nStage2:",cur,"cols Time:",mstime(),"ms\n");
//#include "dualswap.h"
endsearch3:;
if(checkb){
print("\nverifying linear search");
checkdup();}
print("\n\n\n\nSTage3:",fail,"fails",cur,"cols Time:",mstime(),"ms\n");
endsearch:;
A=fstgcols(A);;//switch randomly
end2:;
uint64_t rsw=randuint64();

if(!(rsw&7))A=rndcell();
B=rndcell();
if(A==B)goto end2;
#ifdef VERBOSE
info("PreswapE:");//preswap
#endif
dir=1;swapc(A,B);cur=countudiag();
if(cur>best){dir=-1;fail++;
swapc(A,B);goto end2;}
tfail+=fail;swapt+=swaps;
info("SwapE");
fail=0;swaps=0;best=cur;//new record
if(cur==0){info("Solved:");return;}
goto endsearch;
}
