void integrity(){
//pedantic checks
char __attribute__((unused))  tt2;
if(sumL+sumR){print("\nInvalid sumL+sumR to N=",N,"Collisions:",sumL+sumR);fflush(stdout); tt2=getchar();exit(31);}else{
if(N>100000){print("\nWarning:",N," >100000 slow checks");}
size_t fdg=diags(board,N);
if(fdg){print("\nUnsolved collision at column:",fdg,"/",N,"Reported Collisions:",sumL+sumR);fflush(stdout); tt2=getchar();exit(32);}
} print("\nAll checks passed!\n");
}
