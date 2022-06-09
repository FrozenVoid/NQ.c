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
swapc(A,B);cur=countudiag();
if(cur>best){incfails();
swapc(A,B);
#ifdef VERBOSE
info("FailFDG:");//fail test
#endif
goto fastdiag_start;}
if(fastlim--)goto fastdiag_start;
}
