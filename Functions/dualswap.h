//dual swap algo
while(cur>2){
A=fstgcols(A);
do{B=fstgcols(B);}while(A==B);
info();//new iteration update
dir=1;swapc(A,B);cur=countudiag();
if(cur>best){dir=-1;fail++;
swapc(A,B);continue;}
fail+=fail;swapt+=swaps;
fail=0;swaps=0;best=cur;//new record
if(cur==0)break;

}
