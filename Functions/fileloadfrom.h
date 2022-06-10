#ifdef NOFILEINPUT
#define fileloadfrom(...)
#define pipestdin(...)
#else
void pipestdin(){//assumed to be rows 0..N-1
setbuf(stdin, NULL);
for(size_t i=0;i<N;i++){
uint64_t inp;scanf("%"SCNu64, &inp);
getchar();
board[i]=(val_t)inp;}}

void fileloadfrom(char* name){
if(!strcmp(name,"stdin")){pipestdin();goto filever;}
FILE* in=fopen(name,"rb");
if(!in){print("File:",name," cannot be opened");perror("");exit(111);}
size_t vfqsize=fread(board,sizeof(val_t),N,in);
if(vfqsize!=N){ print("File:",name,"reading failed at  queen#",vfqsize);perror("");exit(112);}
fclose(in);
//verify values in range
filever:;
for(size_t i=0;i<N;i++){
if(board[i]>=N){print("invalid file data at col",i,":",board[i],">=",N);
exit(99);

}}

print("Loaded ",sizeof(val_t),"byte NQ file:",name," N=",N);
}
#endif
