/* Copyright (C) 2017 Embecosm Limited and University of Bristol

   Contributor Graham Markall <graham.markall@embecosm.com>

   This file is part of Embench and was formerly part of the Bristol/Embecosm
   Embedded Benchmark Suite.

   SPDX-License-Identifier: GPL-3.0-or-later */

#include <support.h>

void initialise_board()
{
  asm volatile ("li a0, 0" : : : "a0");
}

void start_trigger()
{
  // Use 91 as a syscall to print the clock at the start trigger
  register long a7 asm("a7") = 91;
  asm volatile ("ecall" : : "r"(a7) );
}

void stop_trigger()
{
  // Use 92 as a syscall to print the clock at the stop trigger
  register long a7 asm("a7") = 92;
  asm volatile ("ecall" : : "r"(a7) );
}


