#include <mpi.h>
#include <stdio.h>

int comp_int(const void *a, const void *b) {
  if (*(int*)a == *(int*)b) return 0;
  return *(int*)a < *(int*)b ? -1 : 1;
}

int main(int argc, char **argv) {
  srand(time(NULL));
  int k = 1000;
  int numbers[k], rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_Rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_Size(MPI_COMM_WORLD, &size);

  int rawChunkSize = k / size;
  if (rawChunkSize * size < k) {
    ++rawChunkSize;
  }

  int chunkSize = rank == (size-1) ? (rawChunkSize - (rawChunkSize * size - k)) : rawChunkSize;

  int chunk[chunkSize];
  memcpy(&chunk, &numbers+(rawChunkSize * rank), chunkSize * sizeof(int));
  qsort(chunk, chunkSize, sizeof(int), comp_int);
 
  if (rank == 0) {
    // receive
  } else {
    MPI_send
  
