#ifdef NOSYNTAX
#define syntax(...) exit(1)
#else
void syntax(){puts("Syntax:nq N [p|f|t|i] [filename|sep]\n N=Board size \n p [string]=printboard [separator] \n f=write result as file \nt=test presolved array\n i filename=load u32/u64 queen array filename\n Xs =scramble rows X times(N*X)\n");exit(1);

}
#endif
