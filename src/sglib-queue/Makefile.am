# Makefile.am for building a BEEBS benchmark
#
# Copyright (C) 2013 Embecosm Limited and University of Bristol
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Contributor: James Pallister <james.pallister@bristol.ac.uk>
#
# SPDX-License-Identifier: GPL-3.0-or-later

if ENABLED_BENCHMARK_SGLIB_QUEUE

include $(top_srcdir)/src/common.mk.am

bin_PROGRAMS              = sglib-queue
noinst_LTLIBRARIES        = libsglib-queue.la

sglib_queue_SOURCES       =
libsglib_queue_la_SOURCES = queue.c sglib.h

sglib_queue_LDADD         = $(DUMMY_CRT0) \
                            $(top_builddir)/support/libsupport.la \
                            libsglib-queue.la \
                            $(top_builddir)/support/libbeebsc.la \
                      $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)



endif
