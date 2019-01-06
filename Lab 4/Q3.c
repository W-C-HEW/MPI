#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	int x, y, z;
	int my_rank, p;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	switch(my_rank){
		case 0: x=0; y=1; z=2;
				MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
				MPI_Send(&y, 1, MPI_INT, 2, 43, MPI_COMM_WORLD);
				MPI_Bcast(&z, 1, MPI_INT, 1, MPI_COMM_WORLD);
				break;
		case 1: x=3; y=4; z=5;
				MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
				MPI_Bcast(&y, 1, MPI_INT, 1, MPI_COMM_WORLD);
				break;
		case 2: x=6, y=7, z=8;
				MPI_Bcast(&z, 1, MPI_INT, 0, MPI_COMM_WORLD);
				MPI_Recv(&x, 1, MPI_INT, 0, 43, MPI_COMM_WORLD, &status);
				MPI_Bcast(&y, 1, MPI_INT, 1, MPI_COMM_WORLD);
				break;
	}

	printf("My rank : %d - X = %d, Y = %d, Z = %d\n", my_rank, x, y, z);
	MPI_Finalize();
	/*
		Rank 0: X = 0, Y = 1, Z = 4
		Rank 1: X = 0, Y = 4, Z = 5
		Rank 2: X = 1, Y = 4, Z = 0
	/*
}