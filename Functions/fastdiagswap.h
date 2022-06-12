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
swapauto(A,B);
if(likely(fastlim--))goto fastdiag_start;
}
