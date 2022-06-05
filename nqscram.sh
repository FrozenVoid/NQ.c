gcc nq.c -gdwarf -Ofast -march=native -mtune=native -pipe -onq -DVERBOSE
for (( n=4;n<11111111;n++ ))
do
  echo "Test Scrambled N-Queens= $n  "
   ./nq $n 1sc
done
