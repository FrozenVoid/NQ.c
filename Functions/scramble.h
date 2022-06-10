#ifdef NOSCRAMBLE
#define scramble(...)
#else
void scramble(size_t num){
 print("\nScrambling N=",N," Times:",num,"\n");fflush(stdout);

for(size_t z=0;z<num*N;z++){
val_t c=rndcell();
val_t d=rndcell();
swapq(c,d);}}

#endif
