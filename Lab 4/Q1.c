#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	int my_rank, p, number;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(my_rank == 0){
		printf("Enter a number : ");
		scanf("%d", &number);
		fflush(stdout);
	}

	MPI_Bcast(&number, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);
	if(my_rank != 0){
		printf("The number is %d, from process %d\n", number, my_rank);
	}
	MPI_Finalize();
}