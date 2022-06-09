//------------------------
#ifdef SILENCE
#define info(...)
#else
void info(char* data){
  if(__rdtsc()-cend>NCYCLES  ){
  clock_t Ntime=mstime();
  print("\n",data," cols=",best,"A=",A,"B=",B,"fails:",(fail),"\nswap:",1.0*swapt/Ntime,"fail:",1.0*tfail/Ntime);
  print("\nT:",Ntime,"ms Col%",100.0*(cur)/N,"Swapt",swapt,"Valid%",100.0*swapt/tswaps);cend=__rdtsc();
#ifdef VERBOSE
if(N<64)printgraph();
#endif
  fflush(stdout);}}
#endif
