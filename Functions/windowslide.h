first:;val_t C;//&& cur>stage1
for(size_t i=0;i<N ;i++){innerc:;
if(zerocols(i))continue;
A=i;
second:;lc=0;
do{
B=i+1+modreduce((val_t)randuint64(),N-i-1);}while(lc++<lcmax &&zerocols(B));
midloop:;

dir=1;swapc(A,B);cur=countudiag();
if(cur>best){dir=-1;fail++;
swapc(A,B);goto second;}
tfail+=fail;swapt+=swaps;
info();//new iteration update
fail=0;swaps=0;best=cur;//new record
if(cur==0){goto fin;}
if(cur>minstage2)goto innerc;
#include "endsearch.h"

}