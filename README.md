# csc4760

Template repository for CSC4760/5760

## Vagrantfile

Configuration file for [HashiCorp Vagrant](https://developer.hashicorp.com/vagrant/downloads) to build a VirtualBox VM similar to an HPC node.
Also demonstrates compiling and running both an OpenMP and a hybrid MPI/OpenMP "Hello, world" program.

Currently only supports Intel processors on Windows, macOS, or Linux.
ARM processors (including Apple M1 and M2) still need to be tested, and this file is almost certainly not going to work out of the box.
Some ARM Vagrant boxes only work with VMware or Parallels virtualization software.

This Vagrantfile will configure:

- a 4-core, 8 GB RAM Linux VM running [Rocky Linux](https://rockylinux.org) 8.
- GCC 8.5.0, OpenMPI 4.1.1, and Valgrind 3.19.
- a folder `/vagrant` in the VM that's actually shared from the folder this repository is cloned to.
- a `vagrant` user in the VM that has password-less sudo.

Basic usage:

- Start a new VM from this folder at a command prompt with `vagrant up`.
- Log into the VM from this folder at a command prompt with `vagrant ssh`.
- Edit files as you like in your preferred editor on the host OS (no requirement to use `vi` or `nano` inside the VM if you don't want to), just make sure you save things in the repo folder tree.
- Compile, test, and debug as needed from the `/vagrant` folder in the VM (see below for more details).
- Halt the VM with `vagrant halt` when you're done.
- Optionally, you can delete all the VM internal files from this folder at a command prompt with `vagrant destroy`.

## Makefile.mpi

Makefile tuned for basic MPI compiling, including hybrid MPI/OpenMP.
Presumes your MPI source files will have names like `*_mpi.c` or `*_mpi.cpp`.

Use as `make -f Makefile.omp foo_omp` to compile `foo_omp.c` to an executable, or `make -f Makefile.mpi clean` to remove executables and object files.

## Makefile.omp

Makefile tuned for basic OpenMP compiling.
Presumes your OpenMP source files will have names like `*_omp.c` or `*_omp.cpp`.

Use as `make -f Makefile.omp foo_omp` to compile `foo_omp.c` to an executable, or `make -f Makefile.omp clean` to remove executables and object files.

## Makefile.serial

Makefile tuned for serial compiling.
Honestly could just use `Makefile.omp` since the OpenMP compiler flags won't do anything to a program that doesn't have `#pragma openmp` lines.
But this one presumes your serial source files will have names like `*_serial.c` or `*_serial.cpp`.

Use as `make -f Makefile.serial foo_serial` to compile `foo_serial.c` to an executable, or `make -f Makefile.serial clean` to remove executables and object files.

## hw_serial.c, hw_omp.c, hw_omp_mpi.c, hwpp_serial.cpp, hwpp_omp.cpp, hwpp_omp_mpi.cpp

Basic C and C++ codes for "Hello, world" for single-core, single-process multi-threaded, and multi-process multi-threaded.
Good enough to demonstrate how to run serial, OpenMP, and MPI/OpenMP hybrid codes in the Vagrant VM.
