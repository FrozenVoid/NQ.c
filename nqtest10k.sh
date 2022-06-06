gcc nq.c -gdwarf -Ofast -march=native -mtune=native -pipe -onq -DVERBOSE
for (( n=10000;n>4;n-- ))
do
  echo "Test N-Queens= $n  "
   ./nq $n c
done
