void fastdiagswap(){
 size_t fastlim=NL;
//quick swap for default linear diagonal(/)
/* this code breaks the default
diagL structure where all queens
are on the same diagonal(the central / one)
which create empty slots to be used by
linear search(33% faster).

*/
verbprint("FastDiag:",mstime(),"ms\n");
fastdiag_start:;
do{A=rndcell();	B=rndcell();}while(!freediag(A,B));
verbinfo("MidloopFDG:");//midloop
swapc(A,B);cur=countudiag();
if(cur>best+1){incfails();
swapc(A,B);
verbinfo("FailFDG:");//fail test
goto fastdiag_start;}
if(likely(fastlim--))goto fastdiag_start;
}
