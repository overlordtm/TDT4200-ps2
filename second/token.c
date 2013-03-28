#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

/*

	Output can appear out of order becaues stdout is buffer
	and messages are being sent from other computers on the
	network and nobody guarantees that they will also arrive
	in order.

	So it can be due to buffering (tried fflush, doesnt help)
	or due to network latency.

	I also tried to append time prefix to message.
*/


int main(int argc, char **argv) {
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	printf("%g: Hello from %d/%d\n", MPI_Wtime(), rank, size);
	fflush (stdout);
	int token=0;
	int next = (rank + 1) % size;
	int prev = (rank + size - 1) % size;
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if (rank == 0) {
	token = 42;
	MPI_Ssend(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
	}
	
	MPI_Recv(&token, 1, MPI_INT, prev, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("%g Node %d got token: %d\n", MPI_Wtime(), rank, token);
	fflush(stdout);
	if (rank != 0) 
	MPI_Ssend(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
	
	MPI_Finalize();
	
	return 0;
}
