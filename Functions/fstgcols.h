//first greater than column(s) with collision
static inline val_t fstgcols(const val_t G){
size_t i=G+1;
loop:;
for(;unlikely(i<N)&& likely(qrcount(i)==2);i++);
if((i==N)){i=0;goto loop;}
return i;}



