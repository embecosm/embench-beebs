# Makefile.am for building a BEEBS benchmark
#
# Copyright (C) 2013 Embecosm Limited and University of Bristol
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Contributor: James Pallister <james.pallister@bristol.ac.uk>
#
# SPDX-License-Identifier: GPL-3.0-or-later

if ENABLED_BENCHMARK_SGLIB_HASHTABLE

include $(top_srcdir)/src/common.mk.am

bin_PROGRAMS                  = sglib-hashtable
noinst_LTLIBRARIES            = libsglib-hashtable.la

sglib_hashtable_SOURCES       =
libsglib_hashtable_la_SOURCES = hashtable.c sglib.h

sglib_hashtable_LDADD         = $(DUMMY_CRT0) \
                                $(top_builddir)/support/libsupport.la \
                                libsglib-hashtable.la \
                                $(top_builddir)/support/libbeebsc.la \
                      $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)



endif
