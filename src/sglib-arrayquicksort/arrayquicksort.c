/* BEEBS arraysort benchmark

   This version, copyright (C) 2014-2019 Embecosm Limited and University of
   Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>
   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include <string.h>
#include "support.h"
#include "sglib.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 398

static const int array[100] = {
  14, 66, 12, 41, 86, 69, 19, 77, 68, 38,
  26, 42, 37, 23, 17, 29, 55, 13, 90, 92,
  76, 99, 10, 54, 57, 83, 40, 44, 75, 33,
  24, 28, 80, 18, 78, 32, 93, 89, 52, 11,
  21, 96, 50, 15, 48, 63, 87, 20, 8, 85,
  43, 16, 94, 88, 53, 84, 74, 91, 67, 36,
  95, 61, 64, 5, 30, 82, 72, 46, 59, 9,
  7, 3, 39, 31, 4, 73, 70, 60, 58, 81,
  56, 51, 45, 1, 6, 49, 27, 47, 34, 35,
  62, 97, 2, 79, 98, 25, 22, 65, 71, 0
};

int array2[100];


int
verify_benchmark (int res __attribute ((unused)))
{
  static const int array_exp[100] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99
  };

  return 0 == memcmp (array2, array_exp, 100 * sizeof (array[0]));
}


void
initialise_benchmark (void)
{
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


static int __attribute__ ((noinline))
benchmark_body (int rpt)
{
  int i;

  for (i = 0; i < rpt; i++)
    {
      memcpy (array2, array, 100 * sizeof (array[0]));
      SGLIB_ARRAY_SINGLE_QUICK_SORT (int, array2, 100,
				     SGLIB_NUMERIC_COMPARATOR);
    }

  return 0;
}


/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
