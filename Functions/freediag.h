static inline int freediag(val_t P,val_t S){//Swapped/Position cells diagonals

const val_t lP=board[S]+P;
const val_t rP=board[S]+(N-P);
const val_t lS=board[P]+S;
const val_t rS=board[P]+(N-S);
return (bitset_get(bitdiagL,lP))
+(bitset_get(bitdiagL,lS))
+(!bitset_get(bitdiagR,rP))
+(!bitset_get(bitdiagR,rS));
;}


