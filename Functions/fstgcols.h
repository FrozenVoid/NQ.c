//first greater than column(s) with collision
static inline val_t fstgcols(const val_t G){
size_t i=G+1;const size_t maxN=N;;
fstgcolsloop:;
for(;unlikely(i<maxN);i++){
if((qrcount(i)!=2))return i;};
if((i==maxN)){i=0;goto fstgcolsloop;}
return i;}

