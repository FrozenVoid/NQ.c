#ifdef NOSCRAMBLE
#define scramble(...)
#else
void scramble(size_t num){
 print("\nScrambling N=",N," Times:",num,"\n");fflush(stdout);

for(size_t z=0;z<num;z++){
for(size_t i=0;i<N;i++){
swapq(i,rndcell());}
}}
#endif
