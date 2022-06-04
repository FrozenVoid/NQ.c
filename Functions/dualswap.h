//dual swap algo
while(cur>8){
A=fstgcols(B);B=fstgcols(A);
info();//new iteration update
dir=1;swapc(A,B);cur=countudiag();
if(cur>best){dir=-1;fail++;
swapc(A,B);continue;}
fail+=fail;swapt+=swaps;
fail=0;swaps=0;best=cur;//new record
if(cur==0)break;

}
