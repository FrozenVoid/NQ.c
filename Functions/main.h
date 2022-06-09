int main(int argc,char**argv){

if(argc<2){syntax();}
N=(val_t)strtoull(argv[1],NULL,10);
if(N<MINBOARD)syntax();
size_t colsize=sizeof(val_t)*N;
print("Queen board size=",colsize," bytes\n");

board=calloc(colsize,1);//columns
if(!board){perror("Queen array size too large for malloc");exit(2);}
fflush(stdout);
size_t diagsize=sizeof(val_t)*(N)*2;
print("Diagonal arrays size=",2*diagsize," bytes\n");
diagL=calloc(diagsize,1);
diagR=calloc(diagsize,1);
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}

if(argc>=3){
dofile= !!strchr(argv[2],'f');//file output
doprint=!!strchr(argv[2],'p');//print
 nosolve= !!strchr(argv[2],'t');//presolved
checkb=!!strchr(argv[2],'c');//pedantic check
scram=!! strchr(argv[2],'s');//scramble

}

#ifdef NOPREFETCH
print("\nprefetch disabled");
#endif
#ifdef SILENCE
print("\ninfo() disabled");
#endif
 if(argc==4){//file input
 fileload=!!strchr(argv[2],'i');}
//setup board
if(nosolve){setpresolved();}
else if(!fileload){for(size_t i=0;i<N;i++)board[i]=i;}

print(dofile?"\n[x]file output":"",
doprint?"\n[x]print board rows":"",
nosolve?"\n[x]generate presolved board":"",
checkb?"\n[x]pedantic checks":"",
scram?"\n[x]scramble board":"");

//file input and scramble
if(fileload){fileloadfrom(argv[3]);}
//main func
if(checkb||fileload ){;checkdup();}
if(scram){size_t scrnum=atoi(argv[2]);scramble(scrnum);}
print("\nSolver:\n");solve();
//check it
verifier();
if(checkb){integrity();checkdup();}
//output
if(doprint){char sep=',';
if(!fileload && argc==4)sep=argv[3][0];
printboard(sep);
if(N<64)printgraph();
}
if(dofile){fileboard();}
return 0;}
