//first greater than column(s) with collision
static inline const val_t fstgcols( val_t G){
size_t i=G+1;const size_t maxN=N;;
fstgcolsloop:;
for(;likely(i<maxN) &&(qrcount(i)==2);i++){
;};
if((i==maxN)){i=0;goto fstgcolsloop;}
return i;}

