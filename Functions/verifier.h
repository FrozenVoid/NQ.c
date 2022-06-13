#ifdef NOVERIFIER
#define verifier()
#else
//verify no collisions (diagonals contain Q=1)
void verifier(){
verbprint("Scanning for diagonal collisions: T:",mstime(),"ms\n");
for(size_t i=0;i<N;i++){
size_t left=(diagL[board[i]+i]);
size_t right=(diagR[board[i]+(N-i)]);;
if(left==1 && right==1)continue;

print("Invalid solution to N=",N,"Collision at c,L,R:",i,left,right,"\n");
if(N<1024)printboard(',');
if(N<64)printgraph();
exit(93);
}
verbprint("Verified zero collisions: T:",mstime(),"ms\n");
}
#endif
