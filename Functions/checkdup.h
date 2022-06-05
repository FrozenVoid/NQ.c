void checkdup(){
for(size_t i=0;i<N;i++){
const val_t c=board[i];
for(size_t z=i+1;z<N;z++){
if(board[z]==c){print("Duplicate column data (",c,")at:",z,i,"\n");
print("Press enter to continue/CTRL-C end\n");
char __attribute__((unused))  tt=getchar();;}}
}}
