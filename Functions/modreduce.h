//https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/
 static inline val_t modreduce(val_t x, val_t N) {
return ((sval_t) x * (sval_t) N) >> (sizeof(val_t)*8);}
