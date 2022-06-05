gcc nq.c -Ofast -march=native -mtune=native -pipe -onq
for (( n=4;n<11111111;n++ ))
do
  echo "Test N-Queens= $n  "
   ./nq $n c
done
