
uint8_t nosolve=0,fileload=0,scram=0,doprint=0,dofile=0;
size_t N,A=0,B=1;
boardtype * board;
boardtype * diagL;size_t sumL=0;
boardtype * diagR;size_t sumR=0;
size_t tfail=0, swapt=0,tswaps=0,edge;
size_t   fail=0;
size_t cend,cur,best,limswap=0;
size_t NL;
