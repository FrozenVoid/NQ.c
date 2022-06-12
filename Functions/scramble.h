#ifdef NOSCRAMBLE
#define scramble(...)
#else
void scramble(size_t num){
 print("\nScrambling N=",N," Times:",num,"\n");FLUSH;

for(size_t z=0;z<num*N;z++){
swapq(rndcell(),rndcell());}}

#endif
