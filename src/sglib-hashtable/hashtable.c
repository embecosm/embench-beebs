/* BEEBS hash benchmark

   This version, copyright (C) 2014-2019 Embecosm Limited and University of
   Bristol

   Contributor James Pallister <james.pallister@bristol.ac.uk>
   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include "support.h"
#include <stdio.h>
#include <string.h>
#include "sglib.h"
#include <stdlib.h>

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 222


#define HASH_TAB_SIZE  20

typedef struct ilist
{
  int i;
  struct ilist *next;
} ilist;

ilist *htab[HASH_TAB_SIZE];

#define ILIST_COMPARATOR(e1, e2)    (e1->i - e2->i)

unsigned int
ilist_hash_function (ilist * e)
{
  return (e->i);
}

SGLIB_DEFINE_LIST_PROTOTYPES (ilist, ILIST_COMPARATOR, next)
SGLIB_DEFINE_LIST_FUNCTIONS (ilist, ILIST_COMPARATOR, next)
SGLIB_DEFINE_HASHED_CONTAINER_PROTOTYPES (ilist, HASH_TAB_SIZE,
					  ilist_hash_function)
SGLIB_DEFINE_HASHED_CONTAINER_FUNCTIONS (ilist, HASH_TAB_SIZE,
					 ilist_hash_function)
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


/* BEEBS heap is just an array */

#define HEAP_SIZE 8192
static char heap[HEAP_SIZE];


int
verify_benchmark (int res)
{
  int i;
  struct ilist ii, *nn;

  for (i = 0; i < 100; i++)
    {
      ii.i = array[i];
      nn = sglib_hashed_ilist_find_member (htab, &ii);

      if ((nn == NULL) || (nn->i != array[i]))
	return 0;
    }

  return (100 == res) && check_heap_beebs ((void *) heap);
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
  volatile int cnt;
  int j;

  for (j = 0; j < rpt; j++)
    {
      int i;
      struct ilist ii, *nn, *ll;
      struct sglib_hashed_ilist_iterator it;

      init_heap_beebs ((void *) heap, HEAP_SIZE);
      sglib_hashed_ilist_init (htab);

      for (i = 0; i < 100; i++)
	{
	  ii.i = array[i];
	  if (sglib_hashed_ilist_find_member (htab, &ii) == NULL)
	    {
	      nn = malloc_beebs (sizeof (struct ilist));
	      nn->i = array[i];
	      sglib_hashed_ilist_add (htab, nn);
	    }
	}

      cnt = 0;

      for (ll = sglib_hashed_ilist_it_init (&it, htab);
	   ll != NULL; ll = sglib_hashed_ilist_it_next (&it))
	{
	  cnt++;
	}
    }

  return cnt;
}


/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
