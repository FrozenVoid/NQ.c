//linear ~O(N) NQueens  solver
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>//__rdtsc
#include "standalone/print.h"
#include "standalone/random.h"
#include "standalone/combsort.h"
#include "standalone/hitstat.h"

#include "Functions/macros.h"
#include "Functions/globals.h"


#include "Functions/checkdup.h"
#include "Functions/qcccount.h"

#include "Functions/printboard.h"
#include "Functions/fileboard.h"
#include "Functions/fileloadfrom.h"
#include "Functions/fstgcols.h"
#include "Functions/info.h"
#include "Functions/swapauto.h"

#include "Functions/edgesolver.h"
#include "Functions/lin.h"
#include "Functions/solve.h"
#include "Functions/integrity.h"
#include "Functions/presolve.h"
#include "Functions/scramble.h"
#include "Functions/verifier.h"
#include "Functions/syntax.h"
#include "Functions/main.h"
