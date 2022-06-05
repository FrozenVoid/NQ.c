static inline val_t rndcell(){
 val_t r=modreduce((val_t)randuint64(),N);
 FETC(&board[r],0,0);
 return r;
 }
