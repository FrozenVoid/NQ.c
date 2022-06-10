#ifdef NOFILEOUTPUT
#define fileboard() ;
#else
void fileboard(){char* fname=malloc(126);
sprintf(fname,"%"PRIu64".nq",(u64)N);
FILE*out=fopen(fname,"wb");
verbprint("\nWriting board into",fname);
size_t rfwout=fwrite(board,4,N,out);
if(rfwout==N){print("\nFile:",fname,"\nRecorded board as file\n");}
else{print("\nFile:",fname,"\nWrite mismatch\n",N,"!=",rfwout);}
fclose(out);
}
#endif
