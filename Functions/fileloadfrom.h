#ifdef NOFILEINPUT
#define fileloadfrom(...)
#else
void fileloadfrom(char* name){
FILE* in=fopen(name,"rb");
if(!in){print("File:",name," cannot be opened");perror("");exit(111);}
size_t vfqsize=fread(board,sizeof(val_t),N,in);
if(vfqsize!=N){ print("File:",name,"reading failed at  queen#",vfqsize);perror("");exit(112);}
//verify values in range
for(size_t i=0;i<N;i++){
if(board[i]>=N){print("invalid file data at col",i,":",board[i],">=",N);
exit(99);

}}

print("Loaded ",sizeof(val_t),"byte NQ file:",name," N=",N);
fclose(in);}
#endif
