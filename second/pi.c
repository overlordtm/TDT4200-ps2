#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ITER 1000

/*

				  000
		              /          \
			   000           001
			 /     \        /   \
		       000   010      001    011
		      /  \   /  \     /  \   / \
		   000 100 010 110  001 101 011 111


*/


int isPow2(int a);
int mylog2(int a);

int main(int argc, char **argv) {
	int rank, size;
	int i;
	double local_result;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	/* Each program instance calculates part of the approximation of pi
	   using the formula pi/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - ... */
	/* Rank 0 calculates the elements 0 - (ITER-1) of the sum,
	   rank 1 calculates the elements ITER - (2*ITER-1) of the sum etc. */
	local_result = 0;
	for(i=rank*ITER; i<rank*ITER+ITER; i++) {
		if(i & 1)
			local_result -= 1.0 / (i*2+1);
		else
			local_result += 1.0 / (i*2+1);
	}

	int depth = mylog2(size);
	int levelsize = size;
	double partner_result;	

	for(int j = depth-1; j >= 0; j--) {
		int partner = rank ^ (1<<j);
		levelsize = levelsize>>1; //make it half
		if(rank >= levelsize && rank < (levelsize<<1)) { //right leafs, have to do MPI_Send
			MPI_Ssend(&local_result, 1, MPI_DOUBLE, partner, 0, MPI_COMM_WORLD);
		} else if(rank < levelsize) {
			MPI_Recv(&partner_result, 1, MPI_DOUBLE, partner, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			local_result+=partner_result;
		}
	}

	if(rank==0)
		printf("pi is approximately equal to %f\n", 4 * local_result);

	MPI_Finalize();

	return 0;
}

int mylog2(int a) {
	int l = -1;
	while(a > 0) {
		a = a>>1;
		l++;	
	}
	return l;
}

int isPow2(int a) {
	printf("Checking %d", a);
	while((a && 1) == 0) {
		a = a>>1;
	}
	return (a ^ 1) == 0;
}
