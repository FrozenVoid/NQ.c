size_t diags(val_t*board,size_t len){//first collision
for(size_t i=0;i<len;i++){size_t cur=board[i];
if(!(i&0xfff)){putchar('+');fflush(stdout);}
 for(size_t z=i+1;z<len;z++){
  size_t zqueen=board[z];
 if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){return i; };   }  }
return 0;}
