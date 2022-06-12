gcc nq.c -Ofast -march=native -mtune=native -Wall -Wno-unused -pipe -onq -DSILENCE -DNOFILEINPUT -DNOFILEOUTPUT -DNOPRINTBOARD -DNOINTEGRITY -DNOVERIFIER -DNOPRESOLVED -DNDEBUG -DNOSYNTAX
function scramtest(){
for (( n=0;n<10;n++ ))
  do
     echo "==========Bench Scram= $n s ======="
     ./nq 10000000 "$n s"
     ecode=$?
#halt on non-zero code
     [ $ecode -ne 0 ] && exit
  done
}
time scramtest


