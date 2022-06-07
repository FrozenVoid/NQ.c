//--------mainloop------

void linearsolve(){
 cend=__rdtsc();
 NL=log2index(N);
  lc=0,lcmax=2+((N)/(NL*NL)),minstage2=160+((NL));
  size_t Blim=8+NL*NL;

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"ms\n");goto endl;/*presolved*/}
print("\nSTART:",mstime()," ms Collisions:",cur,"lcmax:",lcmax,"failmax:",minstage2,"\n");fflush(stdout);
//--------Main loop-------------

first:;
A=fstgcols(A);
innerc:;
if(zerocols(A))A=fstgcols(A);
second:;lc=0;

if(cur<Blim)B=rndcell();else{
do{ B=fstgcols(B);}while(A==B);}
midloop:;
#ifdef VERBOSE
info("Midloop:");//midloop test
#endif

dir=1;swapc(A,B);cur=countudiag();
fail+=cur>=best;
if(cur>best){dir=-1;
swapc(A,B);
#ifdef VERBOSE
info("Fail:");//fail test
#endif
goto second;}
tfail+=fail;swapt+=swaps;
info(cur==best?"Swap0:":"Swap+:");//new iteration update
fail=cur>=best?fail:0;swaps=0;best=cur;//new record
if(cur==0){goto fin;}
if(fail<minstage2)goto innerc;
if(cur)goto first;
fin:;
print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
endl:; //end loop
fflush(stdout);}
