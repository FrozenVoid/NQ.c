
print("\n\n\n\n\n\n\n\n\nEndsearch:",cur,"cols Time:",mstime(),"ms\n");
endsearch:;
A=rndcell();
if(!(randuint64()&127))A=fstgcols(B);
B=fstgcols(A);
while(randuint64()&3)B=fstgcols(B);
if(A==B)goto endsearch;
info();//new iteration update
dir=1;swapc(A,B);cur=countudiag();
if(cur>best){dir=-1;fail++;
swapc(A,B);goto endsearch;}
tfail+=fail;swapt+=swaps;
fail=0;swaps=0;best=cur;//new record
if(cur==0)goto fin;
/*if(cur<4){val_t mA=fstgcols(A);
print("\nFInal array:",cur,"\n");
print(mA);while(A!=mA){print(A);A=fstgcols(A);}

goto fin;
}*/
goto endsearch;
