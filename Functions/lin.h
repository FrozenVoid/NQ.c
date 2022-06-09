//----------------main solver func--------
void linearsolve(){
 cend=__rdtsc();
 NL=log2index(N);
  lc=0,lcmax=2+((N)/(NL*NL)),failmax=160+((NL));
  const size_t Blim=8+NL*NL*NL;

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"ms\n");goto endl;/*presolved*/}
print("\nSTART:",mstime()," ms Collisions:",cur,"Blim:",Blim,"failmax:",failmax,"\n");fflush(stdout);

fastdiagswap();
#ifdef VERBOSE
print("Linear:",mstime(),"ms\n");
#endif
first:;
A=fstgcols(A);
innerc:;
if(zerocols(A))A=fstgcols(A);
second:;
///do(fstgcols) while(A==B) prevents infinite loop
if(unlikely(cur<Blim))B=rndcell();else {do{B=fstgcols(B);}while(unlikely(A==B));}
//A==B allowed if cur<Blim(to failmax)
#ifdef VERBOSE
info("Midloop:");//midloop
#endif
setdir(1);swapc(A,B);cur=countudiag();
if(unlikely(cur>best)){setdir(-1);
fail++;incfails();
swapc(A,B);
#ifdef VERBOSE
info("Fail:");//fail test
#endif
goto second;}
;addswap(swaps);
fail=cur>=best?fail:0;
info("Swap:");//fail==0 -> goodswap
setswaps(0);
best=cur;//new record
if(unlikely(cur==0)){goto fin;}
if((fail<failmax))goto innerc;
fail=0;//reset fails at late search
if(cur)goto first;
fin:;
#ifndef SILENCE
print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
#else
print("\nSolved N=",N," at:",mstime(),"ms\n");
#endif
endl:;fflush(stdout);}




