/* Copyright (C) 2019 PISM Authors
 *
 * This file is part of PISM.
 *
 * PISM is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * PISM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PISM; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*!
 * This header contains values set during PISM's configuration process.
 */

#ifndef PISM_CONFIG_HH
#define PISM_CONFIG_HH

namespace pism {

/* Path to PISM's configuration file (/home/zeitz/pism0.7/share/pism/pism_config.nc) */
extern const char *config_file;

/* PISM's revision string (stable v1.2-2-g3e480b22a committed by Constantine Khrulev on 2020-02-13 13:18:02 -0900) */
extern const char *revision;

/* Configuration flags used to build the PETSc library PISM is linked to (--known-level1-dcache-size=32768 --known-level1-dcache-linesize=64 --known-level1-dcache-assoc=8 --known-sizeof-char=1 --known-sizeof-void-p=8 --known-sizeof-short=2 --known-sizeof-int=4 --known-sizeof-long=8 --known-sizeof-long-long=8 --known-sizeof-float=4 --known-sizeof-double=8 --known-sizeof-size_t=8 --known-bits-per-byte=8 --known-memcmp-ok=1 --known-sizeof-MPI_Comm=4 --known-sizeof-MPI_Fint=4 --known-mpi-long-double=1 --known-mpi-int64_t=1 --known-mpi-c-double-complex=1 --known-has-attribute-aligned=1 --with-prefix=/home/albrecht/software/petsc-3.9.1 --with-cc=mpiicc --with-cxx=mpiicpc --with-fc=0 --with-mpi-lib=/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/lib64/libmpi.so --with-mpi-include=/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mpi/include64 --with-blaslapack-dir=/p/system/packages/intel/parallel_studio_xe_2018_update1/compilers_and_libraries_2018.1.163/linux/mkl/lib/intel64 --with-64-bit-indices=1 --known-64-bit-blas-indices --known-mpi-shared-libraries=1 --with-debugging=1 --with-valgrind=1 --with-valgrind-dir=/p/system/packages/valgrind/3.10.1/gnu --with-x=0 --with-ssl=0 --with-batch=1 --with-shared-libraries=1 --with-mpiexec=srun CFLAGS=\\"-fp-model precise -O3 -xHost -mtune=broadwell\\" CXXFLAGS=\\"-fp-model precise -O3 -xHost -mtune=broadwell\\") */
extern const char *petsc_configure_flags;

/* petsc4py version used to build PISM's Python bindings () */
extern const char *petsc4py_version;

/* SWIG version used to build PISM's Python bindings () */
extern const char *swig_version;

/* CMake version used to build PISM (3.10.2) */
extern const char *cmake_version;

/* Equal to 1 if PISM was built with debugging sanity checks enabled, 0 otherwise. */
#define Pism_DEBUG 0

/* Equal to 1 if PISM was built with Jansson, 0 otherwise. */
#define Pism_USE_JANSSON 0

/* Equal to 1 if PISM was built with PROJ, 0 otherwise. */
#define Pism_USE_PROJ 0

/* Equal to 1 if PISM was built with parallel I/O support using NetCDF-4, 0 otherwise. */
#define Pism_USE_PARALLEL_NETCDF4 1

/* Equal to 1 if PISM was built with PNetCDF's parallel I/O support. */
#define Pism_USE_PNETCDF 0

/* Equal to 1 if PISM was built with NCAR's ParallelIO. */
#define Pism_USE_PIO 0

/* Equal to 1 if PISM's Python bindings were built, 0 otherwise. */
#define Pism_BUILD_PYTHON_BINDINGS 0

} // end of namespace pism

#endif /* PISM_CONFIG_HH */
