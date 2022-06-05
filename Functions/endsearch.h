endsearch3:;
print("\n\n\n\n\n\n\n\n\nStage2:",cur,"cols Time:",mstime(),"ms\n");
#include "dualswap.h"
print("\n\n\n\nSTage3:",cur,"cols Time:",mstime(),"ms\n");
endsearch:;
A=fstgcols(A);;//switch randomly
end2:;
uint64_t rsw=randuint64();

if(!(rsw&7))A=rndcell();
B=rndcell();
if(A==B)goto end2;
info();//new iteration update
dir=1;swapc(A,B);cur=countudiag();
if(cur>best){dir=-1;fail++;
swapc(A,B);goto end2;}
tfail+=fail;swapt+=swaps;
fail=0;swaps=0;best=cur;//new record
if(cur==0){print("Endsearch:",cur,"cols\n");goto fin;}
goto endsearch;
