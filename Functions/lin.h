//--------mainloop------

void fastdiagswap(){
 size_t fastlim=NL;
//quick swap for default linear diagonal(/)
/* this code breaks the default
diagL structure where all queens
are on the same diagonal(the central / one)
which create empty slots to be used by
linear search(33% faster).

*/
#ifdef VERBOSE
print("FastDiag:",mstime(),"ms\n");
#endif
fastdiag_start:;
do{A=rndcell();	B=rndcell();}while(freediag(A,B)<2);
#ifdef VERBOSE
info("MidloopFDG:");//midloop
#endif
dir=1;swapdiag(A,B);cur=countudiag();
if(cur>best){dir=-1;
swapdiag(A,B);
#ifdef VERBOSE
info("FailFDG:");//fail test
#endif
goto fastdiag_start;}
if(fastlim--)goto fastdiag_start;
}

//--------mainloop------

void linearsolve(){
 cend=__rdtsc();
 NL=log2index(N);
  lc=0,lcmax=2+((N)/(NL*NL)),minstage2=160+((NL));
  const size_t Blim=8+NL*NL*NL;

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"ms\n");goto endl;/*presolved*/}
print("\nSTART:",mstime()," ms Collisions:",cur,"Blim:",Blim,"failmax:",minstage2,"\n");fflush(stdout);
//--------Main loop-------------

fastdiagswap();
print("Linear:",mstime(),"ms\n");
first:;
A=fstgcols(A);
innerc:;
if(zerocols(A))A=fstgcols(A);
second:;
if(cur<Blim)B=rndcell();else{
do{B=fstgcols(B);}while(A==B);
}
#ifdef VERBOSE
info("Midloop:");//midloop
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
fail=0;
if(cur)goto first;
fin:;
print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
endl:;fflush(stdout);}

