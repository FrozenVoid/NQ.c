//first greater than column(s) with collision
static inline val_t fstgcols(const val_t G){
size_t i=G+1;
loop:;
for(;i<N ;i++){if(qccount(i))return i;}
if((i==N)){i=0;goto loop;}
return i;}



