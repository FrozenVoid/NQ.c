int main(int argc,char**argv){

if(argc<2){syntax();}
N=(val_t)strtoull(argv[1],NULL,10);
if(!N){print("Invalid board configuration\n");exit(0);}

verbprint("Queen board size=",sizeof(val_t)*N," bytes\n");

board=calloc(N,sizeof(val_t));//columns
if(!board){perror("Queen array size too large for malloc");exit(2);}
fflush(stdout);
verbprint("Diagonal arrays size=",sizeof(val_t)*(N)*2," bytes\n");
diagL=calloc((N),2*sizeof(val_t));
diagR=calloc((N),2*sizeof(val_t));
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}

if(argc>=3){
dofile= !!strchr(argv[2],'f');//file output
doprint=!!strchr(argv[2],'p');//print
 nosolve= !!strchr(argv[2],'t');//presolved
scram=!! strchr(argv[2],'s');//scramble

}

#ifdef SILENCE
verbprint("\ninfo() disabled");
#endif
 if(argc==4){//file input
 fileload=!!strchr(argv[2],'i');}
//setup board
if(nosolve){setpresolved();}
else if(!fileload){for(size_t i=0;i<N;i++)board[i]=i;}

verbprint(dofile?"\n[x]file output":"",
doprint?"\n[x]print board rows":"",
nosolve?"\n[x]generate presolved board":"",
scram?"\n[x]scramble board":"");

//file input and scramble
if(fileload){fileloadfrom(argv[3]);}
//main func
;checkdup();//enable all pedantic checks
if(scram){size_t scrnum=atoi(argv[2]);scramble(scrnum);}
verbprint("\nSolver started: T:",mstime(),"ms\n");solve();
//enable all pedantic checks
verifier();integrity();checkdup();
//output
if(doprint){char sep=',';
if(!fileload && argc==4)sep=argv[3][0];
printboard(sep);
if(N<64)printgraph();
}
if(dofile){fileboard();}
return 0;}
