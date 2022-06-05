void fileloadfrom(char* name){
FILE* in=fopen(name,"rb");
if(!in){print("File:",name," cannot be opened");perror("");exit(111);}
size_t vfqsize=fread(board,sizeof(val_t),N,in);
if(vfqsize!=N){ print("File:",name,"reading failed at  queen#",vfqsize);perror("");exit(112);}
print("Loaded ",sizeof(val_t),"byte NQ file:",name," N=",N);
fclose(in);}
