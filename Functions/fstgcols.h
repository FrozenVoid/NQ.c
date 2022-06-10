//first greater than column(s) with collision
static inline val_t fstgcols(const val_t G){
val_t i=G+1;fstgcolsloop:;
for(;unlikely(i<N);i++){
if((qrcount(i)!=2))return i;};
if((i==N)){i=0;goto fstgcolsloop;}
return i;}

