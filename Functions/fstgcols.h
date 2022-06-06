//first greater than column(s) with collision
//return first column(fstcols) if none
val_t fstgcols(val_t G){
for(size_t i=G+1;i<N;i++){
if(qccount(i))return i;};return fstcols();}
