/* Adapted from https://rcc.uchicago.edu/docs/running-jobs/hybrid/ */
#include <stdio.h>
#include <omp.h>
#include "mpi.h"
int main(int argc, char *argv[]) {
  int numprocs, rank, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int iam = 0, np = 1;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs); /* How many MPI ranks/tasks? */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Which rank am I? */
  MPI_Get_processor_name(processor_name, &namelen); /* What host am I on? */
#pragma omp parallel default(shared) private(iam, np)
  {
    np = omp_get_num_threads(); /* How many threads in this task? */
    iam = omp_get_thread_num(); /* Which thread am I? */
    printf("Host %s, process %d of %d, thread %d of %d\n",
           processor_name, rank, numprocs, iam, np);
  }
  MPI_Finalize();
}
