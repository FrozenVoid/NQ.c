//first greater than column(s) with collision
static inline const val_t fstgcols( val_t G){
size_t i=G+1, maxN=N;;
fstgcolsloop:;
if(likely(i==maxN)){i=0;goto fstgcolsloop;}
if(unlikely(qccount(i)))return i;
i++;goto fstgcolsloop;
return i;/*compiler likes end return struct*/}

