# Embench: Open Benchmarks for Embedded Platforms

This repository contains the Embench free and open source benchmark suite.
These benchmarks are designed to test the performance of deeply embedded
systems.  As such they assume the presence of no OS, minimal C library support
and in particular no output stream.

The rationale behind this benchmark is described in "EmbenchTM: An Evolving
Benchmark Suite for Embedded IoT Computers from an Academic-Industrial
Cooperative" by David Patterson, Jeremy Bennett, Palmer Dabbelt, and Cesare
Garlati (see ).

The benchmarks are largely derived from the Bristol/Embecosm Embedded
Benchmark Suite (BEEBS, see http://beebs.eu), which in turn draws its material
from various earlier projects, notably:

- [MiBench](http://vhosts.eecs.umich.edu/mibench);
- [the WCET benchmark collection](http://www.mrtc.mdh.se/projects/wcet/benchmarks.html); 
- [DSPstone](https://www.ice.rwth-aachen.de/research/tools-projects/closed-projects/dspstone/);
- [the Simple Generic Library](http://sglib.sourceforge.net/); and
- [the Nettle low-level cryptographic library](https://www.lysator.liu.se/~nisse/nettle/).

For the reasoning behind the choice of benchmarks in BEEBS, see "BEEBS: Open
Benchmarks for Energy Measurements on Embedded Platforms." by J Pallister, S
Hollis and J Bennett (http://arxiv.org/abs/1308.5174).  For an example of
BEEBS in use, see "Identifying Compiler Options to Minimise Energy Consumption
for Embedded Platforms" by J Pallister, S Hollis and J Bennett
(http://arxiv.org/abs/1303.6485).

## Using the benchmarks

The benchmarks can be used for a range of purposes. The default scripts
provide a framework for measuring execution performance and compiled code
size.  However they can be used for other purposes, such as measuring energy
efficiency of compiled code (the original purpose for developing BEEBS).

The folloing points should be considered when using the benchmarks

- The benchmarks should all compile to fit in 64kB of program space and use no
  more than 16kB of RAM.

- The measurement of execution performance is designed to use "hot" caches.
  Thus each benchmark executes its entire code several times, before starting
  a timing run.

- Execution runs are scaled to take approximately 4 second of CPU time. This
  is large enough to be accurately measured, yet means all 20 tests, including
  cache warm up can be run in a few minutes.

- To facilitate execution on machines of different performance, the tests are
  scaled by the clock speed of the processor.

- The benchmarks are designed to be run on either real or simulated
  hardware. However for meaningful execution performance results any simulated
  hardware must be strictly cycle accurate.

### Licensing

Embench is licensed under the GNU General Public License version 3 (GPL3).
See the COPYING file for details.  Some individual benchmarks are also
available under different licenses.  See the comments in the individual source
files for details.

The code base is OpenChain compliant, with SPDX license identifiers provided
throughout.

## Structure of the repository

The top level directory contains the scripts to build and execute the
benchmarks.  The current version uses GNU Autotools to build the benhmarks and
DejaGnu to run them.  This will be replaced by Python scripts for platform
portability in a future release.  The following are the top level directories.

- `config`: containing a directory for each architecture supported, and within
  that directory subdirectories for board and cpu descriptions.  Configuation
  data can be provided for individual CPUs and individual boards.

- `doc`: The user manual for Embench.

- `m4`: Support for GNU Autotools.

- `src`: The source for the benchmarks, one directory per benchmark.

- `support`: The generic wrapper code for benchmarks, including substitutes
  for some library and emulation functions.

- `testsuite`: The DejanGnu scripts to run the benchmarks

## Compiling

The strength of the benchmark suite is the ability to run on embedded devices,
however the suite can also be compiled to be executed natively. To run
natively configure and compile as follows:

```bash
mkdir bd
cd bd
../configure
make
```

This will create a compiled benchmark in each directory in `bd/src`. However,
the benchmark suite can be cross compiled for a number of architectures and
development boards. Each target needs the prerequisite tools installed:

 * RI5CY Verilator model
 * PicoRV32 Verilator model

Compiling for one these boards will produce executables for that board, which
toggle a specific pin at the beginning and end of the benchmark. This allows
them to be easily hooked up to other tools for time and energy measurements.

In order to compile for a given board, configure must be invoked with the
following options:

```bash
../configure --host=<host> --with-chip=<chip> --with-board=<board>
```

Where `<host>` is the host triple, and `<chip` and `<board>` are the names of
the chip and board directories under the `config` folder in the source tree. For
example, to configure for a speed test on the RI5CY Verilator model use:

```bash
../configure --host=riscv32-unknown-elf --with-chip=speed-test \
            --with-board=ri5cyverilator
```

## Running the tests

All tests provide the functions `initialize_trigger ()`, `start_trigger ()` and
`stop_trigger ()` to control measurement of the test execution (performance,
energy consumed etc). The implementation of these functions should be provided
in `boardsupport.c` for the particular configuration.
