static inline val_t fstcols(){
for(size_t i=0;i<N;i++){if(qccount(i))return i;};return N-1;}
