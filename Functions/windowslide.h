void windowslide(){
first:;
for(size_t i=0;i<N ;i++){innerc:;
if(zerocols(i))continue;
A=i;
second:;lc=0;
do{lc++;
B=i+modreduce((val_t)randuint64(),(val_t)(N-i-1));
}while(lc<lcmax &&zerocols(B));
midloop:;
#ifdef VERBOSE
info("Midloop:");//midloop test
#endif
if(A==B){fail++;
if(fail>minstage2)return esearch();
goto second;}
dir=1;swapc(A,B);cur=countudiag();
fail+=cur>=best;
if(cur>best){dir=-1;
swapc(A,B);
#ifdef VERBOSE
info("Fail:");//fail test
#endif
if(fail>minstage2)return esearch();
goto second;}
tfail+=fail;swapt+=swaps;
info(cur==best?"Swap0:":"Swap+:");//new iteration update
fail=cur>=best?fail:0;swaps=0;best=cur;//new record
if(cur==0){return;}
if(fail<minstage2)goto innerc;
return esearch();
}}
