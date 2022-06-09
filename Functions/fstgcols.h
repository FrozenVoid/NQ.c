//first greater than column(s) with collision
static inline val_t fstgcols(const val_t G){
size_t i=G+1;fstgcolsloop:;
for(;unlikely(i<N)&& likely(zerocols2(i));i++);
if(i==N){i=0;goto fstgcolsloop;}
return i;}

