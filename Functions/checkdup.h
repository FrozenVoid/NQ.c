void printboard(char sep);
void checkdup(){int hasdups=0;
for(size_t i=0;i<N;i++){
const val_t c=board[i];
for(size_t z=i+1;z<N;z++){
if(board[z]==c){hasdups=1;print("\nDuplicate column data (",c,")at:",z,i,"\n");
print("Press enter to continue/CTRL-C end\n");
char __attribute__((unused))  tt=getchar();;}}
}
if(hasdups && N<1024){printboard('.');}
}
