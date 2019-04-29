/* Copyright (C) 2017 Embecosm Limited and University of Bristol

   Contributor Graham Markall <graham.markall@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include <support.h>

void initialise_board()
{
  __asm__ volatile ("li a0, 0" : : : "a0");
}

void start_trigger()
{
  __asm__ volatile ("li a0, 0" : : : "a0");
}

void stop_trigger()
{
  __asm__ volatile ("li a0, 0" : : : "a0");
}


