//first greater than column(s) with collision
static inline const val_t fstgcols( val_t G){
size_t i=G+1;const size_t maxN=N;;
fstgcolsloop:;
if(unlikely(i<maxN)){
if(likely(zerocols2(i))){i++;goto fstgcolsloop;} return i;}

if(likely(i==maxN)){i=0;goto fstgcolsloop;}
return i;}
