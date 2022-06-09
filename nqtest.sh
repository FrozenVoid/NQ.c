#pass any parameters to nq $*
gcc nq.c -gdwarf -Ofast -march=native -mtune=native -pipe -onq -DVERBOSE
for (( n=8;n<11111111;n++ ))
do
  echo "============Test N-Queens= $n ======="
   ./nq $n $*
   ecode=$?
#halt on non-zero code
   [ $ecode -ne 0 ] && exit
done
