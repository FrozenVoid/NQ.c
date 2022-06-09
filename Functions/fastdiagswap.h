void fastdiagswap(){
#if MINBOARD<8
size_t fastlim=1000000000;
#else
 size_t fastlim=NL;
#endif
//quick swap for default linear diagonal(/)
/* this code breaks the default
diagL structure where all queens
are on the same diagonal(the central / one)
which create empty slots to be used by
linear search(33% faster).

*/
verbprint("FastDiag:",mstime(),"ms\n");
fastdiag_start:;
do{A=rndcell();	B=rndcell();}while(freediag(A,B)<2);
verbinfo("MidloopFDG:");//midloop
swapc(A,B);cur=countudiag();
if(cur>best+1){incfails();
swapc(A,B);
verbinfo("FailFDG:");//fail test
goto fastdiag_start;}
best=cur;if(!cur)return;
if(fastlim--)goto fastdiag_start;
}
