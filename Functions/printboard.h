#ifdef NOPRINTBOARD
#define printboard(...)
#define printgraph()
#else
void printboard(char sep){
 printf("\n%"PRIu64"",(uint64_t)board[0]);
for(size_t i=1;i<N;i++){putchar(sep);
printf("%"PRIu64"",(uint64_t)board[i]);}}

void printgraph(){//graphical view
puts("");
for(int64_t zz=N-1;zz>-1;zz--){//row N-1/0
//column ZZ:row cq
for(int64_t k=0;k<N;k++){
printf(zz==board[k]?"Q|":"_|");}puts("");}
}
#endif
