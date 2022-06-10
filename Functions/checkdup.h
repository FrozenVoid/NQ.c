#ifdef NODUPCHECK
#define checkdup() ;
#else
void printboard(char sep);
void checkdup(){int hasdups=0;
verbprint("Beginning duplicate check:N=",N,"  T:",mstime(),"ms\n");
//at this point DiagL array is unused/unset
memcpy(diagL,board,N*sizeof(val_t));
verbprint("Copied temporary array  T:",mstime(),"ms\n");
sortmethod(diagL,N);
verbprint("Sorted temporary array  T:",mstime(),"ms\n");
for(size_t i=1;i<N;i++){
if(diagL[i]!=diagL[i-1])continue;
{hasdups=1;print("\nDuplicate column data (",diagL[i],")at:",i,i-1,"\n");
if(hasdups && N<1024){printboard('.');puts("");}
exit(231);;}}

memset(diagL,0,N*sizeof(val_t));//zero used
verbprint("No duplicates found  T:",mstime(),"ms\n");

}
#endif
