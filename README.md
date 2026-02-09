# csc4760

Template repository for CSC4760/5760

## Vagrantfile

Configuration file for [HashiCorp Vagrant](https://developer.hashicorp.com/vagrant/downloads) to build a VirtualBox VM similar to an HPC node.
Also demonstrates compiling and running both an OpenMP and a hybrid MPI/OpenMP "Hello, world" program.

Currently only supports Intel-compatible processors on Windows, macOS, or Linux.
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

Use as `make -f Makefile.mpi foo_mpi` to compile `foo_mpi.c` or `foo_mpi.cpp` to an executable, or `make -f Makefile.mpi clean` to remove executables and object files.

## Makefile.omp

Makefile for basic OpenMP compiling.
Presumes your OpenMP source files will have names like `*_omp.c` or `*_omp.cpp`.

Use as `make -f Makefile.omp foo_omp` to compile `foo_omp.c` or `foo_omp.cpp` to an executable, or `make -f Makefile.omp clean` to remove executables and object files.

## Makefile.serial

Makefile for serial compiling.
Functionally identical to `Makefile.omp`, since the OpenMP compiler flags won't do anything to a program that doesn't have `#pragma openmp` lines.
But this one presumes your serial source files will have names like `*_serial.c` or `*_serial.cpp`.

Use as `make -f Makefile.serial foo_serial` to compile `foo_serial.c` or `foo_serial.cpp` to an executable, or `make -f Makefile.serial clean` to remove executables and object files.

## hw_serial.c, hw_omp.c, hw_omp_mpi.c, hwpp_serial.cpp, hwpp_omp.cpp, hwpp_omp_mpi.cpp

Basic C and C++ codes for "Hello, world" for single-core, single-process multi-threaded, and multi-process multi-threaded.
Good enough to demonstrate how to run serial, OpenMP, and MPI/OpenMP hybrid codes in the Vagrant VM.

## `kokkos` folder

This contains one example from [the Kokkos repository](https://github.com/kokkos/kokkos/tree/develop/example/tutorial/01_hello_world) and a second from [the Kokkos Tutorials repository](https://github.com/kokkos/kokkos-tutorials/tree/main/Exercises/multi_gpu_cuda).
Each has a CMakeLists.txt file compatible with the Kokkos installations on the TN Tech HPC.

To compile and build `01_hello_world` on the TN Tech HPC, ssh to login.hpc.tntech.edu, `cd` to your `01_hello_world` directory, and then:

1. From the `$` prompt on `login.hpc.tntech.edu`, type `hpcshell --cpus-per-task=2 --account=csc4760-001-2026s`.
2. Wait for the interactive session to start, and you'll see a `$` prompt from an available compute node.
3. Load the non-CUDA-enabled version of Kokkos 4.7 with `spack load kokkos@4.7~cuda cmake gcc@14`.
4. Configure and compile your source file with `mkdir build ; cd build ; cmake .. ; make`
5. Assuming you get no errors, run your executable with `./tutorial_01_hello_world` (or whatever the name of your final executable is).
6. Debug, recompile, and rerun your code as needed.
7. When everything works, remove the build folder with `cd .. ; rm -rf build`.
8. Type `exit` to get back to the login node.

To compile and build `01_hello_world` on the TN Tech HPC, ssh to login.hpc.tntech.edu, `cd` to your `multi_gpu_cuda` directory, and then:

1. From the `$` prompt on `login.hpc.tntech.edu`, type `hpcshell --cpus-per-task=2 --gpus-per-task=1 --account=csc4760-001-2026s`.
2. Wait for the interactive session to start, and you'll see a `$` prompt from a compute node with an available GPU.
3. Load the CUDA-enabled version of Kokkos 4.7 with `spack load kokkos@4.7+cuda cmake gcc@14`.
4. Configure and compile your source file with `mkdir build ; cd build ; cmake .. ; make`
5. Assuming you get no errors, run your executable with `./tutorial_01_hello_world` (or whatever the name of your final executable is).
6. Debug, recompile, and rerun your code as needed.
7. When everything works, remove the build folder with `cd .. ; rm -rf build`.
8. Type `exit` to get back to the login node.