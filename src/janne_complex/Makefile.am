# Makefile.am for building a BEEBS benchmark
#
# Copyright (C) 2014 Embecosm Limited and University of Bristol
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Contributor: James Pallister <james.pallister@bristol.ac.uk>
#
# SPDX-License-Identifier: GPL-3.0-or-later

if ENABLED_BENCHMARK_JANNE_COMPLEX

include $(top_srcdir)/src/common.mk.am

bin_PROGRAMS                = janne_complex
noinst_LTLIBRARIES          = libjanne_complex.la

janne_complex_SOURCES       =
libjanne_complex_la_SOURCES = libjanne_complex.c

janne_complex_LDADD         = $(DUMMY_CRT0) \
                              $(top_builddir)/support/libsupport.la \
                              libjanne_complex.la \
                              $(top_builddir)/support/libbeebsc.la \
                      $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)



endif
