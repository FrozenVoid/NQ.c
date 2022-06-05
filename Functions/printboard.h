void printboard(char sep){
 printf("\n%"PRIu64"",(uint64_t)board[0]);
for(size_t i=1;i<N;i++){
printf("%c%"PRIu64"",sep,(uint64_t)board[i]);}}
