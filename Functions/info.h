//------------------------
#ifdef SILENCE
#define info()
#else
 void info(){
  if(__rdtsc()-cend>NCYCLES  ){
  clock_t Ntime=mstime();
  print("\n cols=",best,"A=",A,"B=",B,"valid/fail:",swaps,"/",(fail),"\nswap:",1.0*swapt/Ntime,"fail:",1.0*tfail/Ntime);
  print("\nT:",Ntime,"ms Col%",100.0*(cur)/N,"Swapt",swapt,"Valid%",100.0*swapt/tswaps);cend=__rdtsc();fflush(stdout);}}
#endif
