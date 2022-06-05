static inline val_t rndcell(){
 val_t r=modreduce((val_t)randuint64(),N);
FETC(&board[r],0,2);
FETC(&diagL[board[r]+r],0,2);
FETC(&diagR[board[r]+(N-r)],0,2);
 return r;
 }

static inline val_t rndcell2(val_t start,val_t rangemax){
 val_t r=start+modreduce((val_t)randuint64(),rangemax);
//prefetch earlier for diagonal data
FETC(&board[r],0,2);
FETC(&diagL[board[r]+r],0,2);
FETC(&diagR[board[r]+(N-r)],0,2);

 return r;
 }
