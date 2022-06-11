//first greater than column(s) with collision
static inline const val_t fstgcols( val_t G){
size_t i=G+1; size_t maxN=N;;
fstgcolsloop:;
if(likely(i<maxN)){
if(likely(zerocols2(i))){i++;goto fstgcolsloop;} return i;}else
if(likely(i==maxN)){i=0;goto fstgcolsloop;}
return i;/*compiler likes end return struct*/}
