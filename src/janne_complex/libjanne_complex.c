/* BEEBS janne_complex benchmark

   This version, copyright (C) 2014-2019 Embecosm Limited and University of
   Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>
   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

/*----------------------------------------------------------------------
 *  WCET Benchmark created by Andreas Ermedahl, Uppsala university,
 *  May 2000.
 *
 *  The purpose of this benchmark is to have two loop where the inner
 *  loops max number of iterations depends on the outer loops current
 *  iterations.  The results corresponds to something Jannes flow-analysis
 *  should produce.
 *
 * The example appeard for the first time in:
 *
 *  @InProceedings{Ermedahl:Annotations,
 * author =       "A. Ermedahl and J. Gustafsson",
 * title =        "Deriving Annotations for Tight Calculation of Execution Time",
 * year =         1997,
 * month =        aug,
 * booktitle =    EUROPAR97,
 * publisher =    "Springer Verlag",
 * pages =        "1298-1307"
 * }
 *
 * The result of Jannes tool is something like:
 *   outer loop:       1   2   3   4   5   6   7   8   9   10   11
 *   inner loop max:   5   9   8   7   4   2   1   1   1   1    1
 *
 *----------------------------------------------------------------------*/

#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 23667


int
complex (int a, int b)
{
  while (a < 30)
    {
      while (b < a)
	{
	  if (b > 5)
	    b = b * 3;
	  else
	    b = b + 2;
	  if (b >= 10 && b <= 12)
	    a = a + 10;
	  else
	    a = a + 1;
	}
      a = a + 2;
      b = b - 10;
    }
  return 1;
}

static int benchmark_body (int  rpt);

void
warm_caches (int  heat)
{
  int  res = benchmark_body (heat);

  return;
}


int
benchmark (void)
{
  return benchmark_body (LOCAL_SCALE_FACTOR * CPU_MHZ);
}


static int a, b;

static int __attribute__ ((noinline))
benchmark_body (int rpt)
{
  volatile int answer = 0;
  int i;

  for (i = 0; i < rpt; i++)
    {
      /* a = [1..30] b = [1..30] */
      answer = 0;
      a = 1;
      b = 1;
      /* if(answer)
         {a = 1; b = 1;}
         else
         {a = 30; b = 30;} */
      answer = complex (a, b);
    }

  return answer;
}

void
initialise_benchmark ()
{
}

int
verify_benchmark (int r)
{
  return 1 == r;
}


/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
