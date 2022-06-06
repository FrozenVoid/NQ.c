//--------mainloop------

void linearsolve(){
 cend=__rdtsc();
 NL=log2index(N);
  lc=0,lcmax=2+((N)/(NL*NL)),minstage2=160+((NL)),endsearch=(NL/2)*(NL/2),Blim=8+NL;

 cur=countudiag(),best=cur;if(cur==0){print("\nPre-Solved N=",N," at:",mstime(),"\n");goto endl;/*presolved*/}
print("\nSTART:",mstime()," ms Collisions:",cur,"\n");fflush(stdout);
//--------Main loop-------------

windowslide();
print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
endl:; //end loop
fflush(stdout);}
