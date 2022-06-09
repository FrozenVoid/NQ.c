#ifdef NOINTEGRITY
#define checkdup() ;
#else
void printboard(char sep);
void checkdup(){int hasdups=0;
print("Beginning duplicate check:N=",N,"\n");
//at this point DiagL array is unused/unset
memcpy(diagL,board,N*sizeof(val_t));
combsort(diagL,N);
for(size_t i=1;i<N;i++){
if(diagL[i]==diagL[i-1]){hasdups=1;print("\nDuplicate column data (",diagL[i],")at:",i,i-1,"\n");
if(hasdups && N<1024){printboard('.');puts("");}
exit(231);;}}

memset(diagL,0,N*sizeof(val_t));//zero used
print("No duplicates found\n");

}
#endif
