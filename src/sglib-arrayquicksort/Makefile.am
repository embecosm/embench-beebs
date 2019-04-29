# Makefile.am for building a BEEBS benchmark
#
# Copyright (C) 2013 Embecosm Limited and University of Bristol
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Contributor: James Pallister <james.pallister@bristol.ac.uk>
#
# SPDX-License-Identifier: GPL-3.0-or-later

if ENABLED_BENCHMARK_SGLIB_ARRAYQUICKSORT

include $(top_srcdir)/src/common.mk.am

bin_PROGRAMS                        = sglib-arrayquicksort
noinst_LTLIBRARIES                  = libsglib-arrayquicksort.la

sglib_arrayquicksort_SOURCES        =

libsglib_arrayquicksort_la_SOURCES  = arrayquicksort.c sglib.h
libsglib_arrayquicksort_la_CPPFLAGS = -DQUICK_SORT ${AM_CPPFLAGS}

sglib_arrayquicksort_LDADD          = $(DUMMY_CRT0) \
                                      $(top_builddir)/support/libsupport.la \
                                      libsglib-arrayquicksort.la \
                                      $(top_builddir)/support/libbeebsc.la \
                      $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)

endif
