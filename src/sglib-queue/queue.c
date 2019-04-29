/* BEEBS queue benchmark

   This version, copyright (C) 2014-2019 Embecosm Limited and University of
   Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>
   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include "support.h"
#include <stdio.h>
#include <stdlib.h>
#include "sglib.h"
#include <stdlib.h>

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 133

#define MAX_PARAMS 101

typedef struct iq
{
  int a[MAX_PARAMS];
  int i, j;
} iq;
SGLIB_DEFINE_QUEUE_FUNCTIONS (iq, int, a, i, j, MAX_PARAMS)
     int array[100] =
       { 14, 66, 12, 41, 86, 69, 19, 77, 68, 38, 26, 42, 37, 23, 17, 29, 55,
13,
       90, 92, 76, 99, 10, 54, 57, 83, 40, 44, 75, 33, 24, 28, 80, 18, 78, 32,
	 93, 89, 52, 11,
       21, 96, 50, 15, 48, 63, 87, 20, 8, 85, 43, 16, 94, 88, 53, 84, 74, 91,
	 67, 36, 95, 61,
       64, 5, 30, 82, 72, 46, 59, 9, 7, 3, 39, 31, 4, 73, 70, 60, 58, 81, 56,
	 51, 45, 1, 6, 49,
       27, 47, 34, 35, 62, 97, 2, 79, 98, 25, 22, 65, 71, 0
     };

void
initialise_benchmark (void)
{
}



int
benchmark ()
{
  volatile int cnt;
  int j;

  for (j = 0; j < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); j++)
    {
      int i, ai, aj, n;
      int a[MAX_PARAMS];
      cnt = 0;

      // echo parameters using a queue
      SGLIB_QUEUE_INIT (int, a, ai, aj);
      for (i = 0; i < 100; i++)
	{
	  n = array[i];
	  SGLIB_QUEUE_ADD (int, a, n, ai, aj, MAX_PARAMS);
	}
      while (!SGLIB_QUEUE_IS_EMPTY (int, a, ai, aj))
	{
	  cnt += SGLIB_QUEUE_FIRST_ELEMENT (int, a, ai, aj);
	  SGLIB_QUEUE_DELETE (int, a, ai, aj, MAX_PARAMS);
	}

      // print parameters in descending order
      SGLIB_HEAP_INIT (int, a, ai);
      for (i = 0; i < 100; i++)
	{
	  n = array[i];
	  SGLIB_HEAP_ADD (int, a, n, ai, MAX_PARAMS,
			  SGLIB_NUMERIC_COMPARATOR);
	}
      while (!SGLIB_HEAP_IS_EMPTY (int, a, ai))
	{
	  cnt += SGLIB_HEAP_FIRST_ELEMENT (int, a, ai);
	  SGLIB_HEAP_DELETE (int, a, ai, MAX_PARAMS,
			     SGLIB_NUMERIC_COMPARATOR);
	}
    }

  return cnt;
}

int
verify_benchmark (int r)
{
  return 9900 == r;
}


/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
