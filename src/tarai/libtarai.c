/* BEEBS tarai benchmark

   This version, copyright (C) 2014-2019 Embecosm Limited and University of
   Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>
   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 6655

int
tarai (int x, int y, int z)
{
  int ox = x;
  int oy = y;

  while (x > y)
    {
      ox = x;
      oy = y;

      x = tarai (x - 1, y, z);
      y = tarai (y - 1, z, ox);

      if (x <= y)
	break;

      z = tarai (z - 1, ox, oy);
    }

  return y;
}

int x, y, z;

int
benchmark ()
{
  volatile int cnt;
  int i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    cnt = tarai (x, y, z);

  return cnt;
}

void
initialise_benchmark ()
{
  x = 9;
  y = 6;
  z = 3;
}

int
verify_benchmark (int r)
{
  return 9 == r;
}


/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
