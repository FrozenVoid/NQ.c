//verify no collisions (diagonals contain Q=1)
void verifier(){
for(size_t i=0;i<N;i++){
//halt on error(stops nqtest.sh)
val_t left=(diagL[board[i]+i]);
val_t right=(diagR[board[i]+(N-i)]);;
if(left||right){
print("Invalid solution to N=",N,"Collision at c,L,R:",i,left,right);
fflush(stdout);
char __attribute__((unused))  tt=getchar();return;}
}}
