/* BEEBS rbtree benchmark

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
#define LOCAL_SCALE_FACTOR 85


typedef struct rbtree
{
  int n;
  char color_field;
  struct rbtree *left;
  struct rbtree *right;
} rbtree;

#define CMPARATOR(x,y) ((x->n)-(y->n))

SGLIB_DEFINE_RBTREE_PROTOTYPES (rbtree, left, right, color_field, CMPARATOR)
SGLIB_DEFINE_RBTREE_FUNCTIONS (rbtree, left, right, color_field, CMPARATOR)
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
      int i;
      struct rbtree e, *t, *the_tree, *te;
      struct sglib_rbtree_iterator it;
      cnt = 0;

      init_heap_beebs ((void *) heap, HEAP_SIZE);
      the_tree = NULL;
      for (i = 0; i < 100; i++)
	{
	  e.n = array[i];
	  if (sglib_rbtree_find_member (the_tree, &e) == NULL)
	    {
	      t = malloc_beebs (sizeof (struct rbtree));
	      t->n = array[i];
	      sglib_rbtree_add (&the_tree, t);
	    }
	}

      for (te = sglib_rbtree_it_init_inorder (&it, the_tree);
	   te != NULL; te = sglib_rbtree_it_next (&it))
	{
	  cnt += te->n;
	}
    }

  return cnt;
}


int
verify_benchmark (int r)
{
  return (4950 == r) && check_heap_beebs ((void *) heap);
}


/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
