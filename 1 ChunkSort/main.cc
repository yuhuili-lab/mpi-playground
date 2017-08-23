// Sort 100 integers by dividing them up into n parts, send to (n-1) processes to sort each chunk, finally combine them back to give result.

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int comp_int(const void *a, const void *b) {
  if (*(int*)a == *(int*)b) return 0;
  return *(int*)a < *(int*)b ? -1 : 1;
}

int main(int argc, char **argv) {
  srand(time(NULL));
  int k = 100; // number of integers
  int mpi_rank, mpi_size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  
  int chunkSize = k / mpi_size;
  
  if (chunkSize * mpi_size < k) {
    cerr << "Number of processes must evenly divide 100." << endl;
    return 1;
  }
  
  if (mpi_rank == 0) { // Master
    int numbers[k];
    for (int i = 0; i < k; ++i) {
      numbers[i] = rand() % 10000; // for readability
    }
    
    int rezNumbers[mpi_size][chunkSize];
    
    // Send to slaves for processing
    for (int i = 1; i < mpi_size; ++i) {
      MPI_Send(&numbers[i*chunkSize], chunkSize, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Recv(&rezNumbers[i], chunkSize, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    // Master sort first chunk
    memcpy(&rezNumbers[0], &numbers, chunkSize * sizeof(int));
    qsort(rezNumbers[0], chunkSize, sizeof(int), comp_int);
    
    // Stitch up all arrays
    // Left as an exercise for reader: use a min-heap
    for (int i = 0; i < mpi_size; ++i) {
      cout << "Chunk #" << i << ": " << endl;
      for (int j = 0; j < chunkSize; ++j) {
        cout << rezNumbers[i][j] << ", ";
      }
      cout << endl;
    }
    cout << "TODO: Stitch up all arrays" << endl;
    cout << "Left as an exercise for reader: use a min-heap" << endl;
  } else { // Slave
    int chunk[chunkSize];
    MPI_Recv(&chunk, chunkSize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    qsort(chunk, chunkSize, sizeof(int), comp_int);
    MPI_Send(&chunk, chunkSize, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
  
  return 0;
}
