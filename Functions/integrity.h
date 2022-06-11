#ifdef NOINTEGRITY
#define integrity()
#else
void integrity(){
int hasdups=0,hasdupsR=0,hasdupsL=0;
if(sumL+sumR){print("\nInvalid sumL+sumR to N=",N,"Collisions:",sumL+sumR);FLUSH; ;exit(31);}
//uses diagX arrays as they are unused
verbprint("Preparing integrity check for diagonals T:",mstime(),"ms\n");
for(size_t i=0;i<N;i++){
diagL[i]=board[i]+i;
diagR[i]=board[i]+(N-i);}
verbprint("Sorting diagonals T:",mstime(),"ms\n");
sortmethod(diagL,N);
sortmethod(diagR,N);
verbprint("Scanning for duplicate data in DiagL array T:",mstime(),"ms\n");
for(size_t i=1;i<N;i++){
if(diagL[i]==diagL[i-1]){hasdups=1;hasdupsL=i;print("\nDuplicate left diagonal  data (",diagL[i],")at:",i,i-1,"\n");
goto integerror;;}}

verbprint("Scanning for duplicate data in DiagR array T:",mstime(),"ms\n");
for(size_t i=1;i<N;i++){
if(diagR[i]==diagR[i-1]){hasdups=1;hasdupsR=i;print("\nDuplicate right diagonal  data (",diagR[i],")at:",i,i-1,"\n");
goto integerror;}}

integerror:;
if(hasdups){print("\nUnsolved collision at diagonalL:",hasdupsL,"diagonalR",hasdupsR,":","Reported Collisions:",sumL+sumR,"\nCtrl-C to end program/enter=exit");FLUSH;
if(N<64)printgraph();
;exit(32);}
 verbprint("\nIntegrity checks passed! T:",mstime(),"ms \n");
}
#endif
