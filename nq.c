//linear ~O(N) NQueens  solver
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>//__rdtsc
#include "standalone/print.h"//required
#include "standalone/random.h"//required
#include "standalone/combsort.h"//for checks
#include "standalone/hitstat.h"//optional

#include "Functions/macros.h"
#include "Functions/globals.h"


#include "Functions/checkdup.h"//-DDUPCHECK
#include "Functions/qcccount.h"

#include "Functions/printboard.h"//-DNOPRINTBOARD
#include "Functions/fileboard.h"// -DNOFILEOUTPUT
#include "Functions/fileloadfrom.h"//-DNOFILEINPUT
#include "Functions/fstgcols.h"
#include "Functions/info.h"// -DSILENCE
#include "Functions/swapauto.h"

#include "Functions/edgesolver.h"
#include "Functions/lin.h"
#include "Functions/solve.h"
#include "Functions/integrity.h"// -DNOINTEGRITY
#include "Functions/presolve.h"// -DNOPRESOLVED
#include "Functions/scramble.h"// -DNOSCRAMBLE
#include "Functions/verifier.h"// -DNOVERIFIER
#include "Functions/syntax.h"// -DNOSYNTAX
#include "Functions/main.h"
