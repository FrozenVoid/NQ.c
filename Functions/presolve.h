void setpresolved(){
if(N%6<2||N%6>=4){// presolved: place knight diagonals
for(size_t i=0,z=1;i<N;i++,z+=2){
if(z>=N){z=0;}board[i]=z;;}
}else if(N%6==2){
for(size_t i=0,z=1;z<N;i++,z+=2){board[i]=z;}
for(size_t i=N/2,z=2;z &&i<N;i++,z-=2){board[i]=z;}
for(size_t i=2+N/2,z=6;z<N-1 &&i<N;i++,z+=2){board[i]=z;}
board[N-1]=4;
}else if(N%6==3){size_t c9,z;

for(c9=0,z=3;z<N-1;c9++,z+=2){board[c9]=z;}
board[c9++]=1;
for(z=4;c9<N-2;c9++,z+=2){board[c9]=z;}
board[c9++]=0;board[c9++]=2;
}}
