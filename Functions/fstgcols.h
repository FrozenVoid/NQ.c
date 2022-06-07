//first greater than column(s) with collision
//return first column(fstcols) if none
static inline val_t fstgcols(const val_t G){
size_t i=G+1;
for(;i<N &&!qccount(i) ;i++);

if(i==N)return fstcols();
return i;}
