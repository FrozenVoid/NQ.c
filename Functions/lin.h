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
do{A=rndcell();	B=rndcell();}while(		freediag(A,B)<2);
#ifdef VERBOSE
info("MidloopFDG:");//midloop
#endif
dir=1;swapc(A,B);cur=countudiag();
if(cur>best){dir=-1;
swapc(A,B);
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
  lc=0,lcmax=2+((N)/(NL*NL)),failmax=160+((NL));
  const size_t Blim=8+NL*NL*NL;

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"ms\n");goto endl;/*presolved*/}
print("\nSTART:",mstime()," ms Collisions:",cur,"Blim:",Blim,"failmax:",failmax,"\n");fflush(stdout);
//--------Main loop-------------

fastdiagswap();
#ifdef VERBOSE
print("Linear:",mstime(),"ms\n");
#endif
first:;
A=fstgcols(A);
innerc:;
if(zerocols(A))A=fstgcols(A);
second:;
B=cur<Blim?rndcell():fstgcols(B);
#ifdef VERBOSE
info("Midloop:");//midloop
#endif
if(unlikely(A==B))goto second;
setdir(1);swapc(A,B);cur=countudiag();
fail+=(cur>=best);
if(cur>best){setdir(-1);
swapc(A,B);
#ifdef VERBOSE
info("Fail:");//fail test
#endif
goto second;}
addfail(fail);addswap(swaps);

info(cur==best?"Swap0:":"Swap+:");//new iteration update
setswaps(0);
fail=cur>=best?fail:0;
best=cur;//new record
if(cur==0){goto fin;}
if(fail<failmax)goto innerc;
if(cur)goto first;
fin:;
#ifndef SILENCE
print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
#else
print("\nSolved N=",N," at:",mstime(),"ms\n");
#endif
endl:;fflush(stdout);}

