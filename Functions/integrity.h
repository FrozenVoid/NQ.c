void integrity(){
//pedantic checks
int hasdups=0,hasdupsR=0,hasdupsL=0;
if(sumL+sumR){print("\nInvalid sumL+sumR to N=",N,"Collisions:",sumL+sumR);fflush(stdout); char __attribute__((unused))  tt2x=getchar();exit(31);}
//uses diagX arrays as they are unused
for(size_t i=0;i<N;i++){
diagL[i]=board[i]+i;
diagR[i]=board[i]+(N-i);}
combsort(diagL,N);
combsort(diagR,N);
for(size_t i=1;i<N;i++){
if(diagL[i]==diagL[i-1]){hasdups=1;hasdupsL=i;print("\nDuplicate left diagonal  data (",diagL[i],")at:",i,i-1,"\n");
print("Press enter to continue/CTRL-C end\n");
char __attribute__((unused))  tt=getchar();;}}
for(size_t i=1;i<N;i++){
if(diagR[i]==diagR[i-1]){hasdups=1;hasdupsR=i;print("\nDuplicate right diagonal  data (",diagR[i],")at:",i,i-1,"\n");
print("Press enter to continue/CTRL-C end\n");
char __attribute__((unused))  tt2=getchar();;}}

if(hasdups){print("\nUnsolved collision at diagonalL:",hasdupsL,"diagonalR",hasdupsR,":","Reported Collisions:",sumL+sumR,"\nCtrl-C to end program/enter=exit");fflush(stdout); char __attribute__((unused))  tt3=getchar();exit(32);}
 print("\nIntegrity checks passed!\n");
}
