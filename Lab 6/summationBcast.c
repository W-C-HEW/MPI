#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	int my_rank, p;
	int number, i, sum=0;
	char *endPoint;
	int* data;
	double startTime, endTime;
	const int tag=40;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	startTime = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	number = strtol(argv[1], &endPoint, 10); //get input
	data = malloc(number*sizeof(int)); //allocate memory

	if(my_rank == 0){
		for(i=0; i<number; i++){ //initialize inters in array
			data[i] = i+1;
		}
	}

	MPI_Bcast(data, number, MPI_INT, 0, MPI_COMM_WORLD);

	if(my_rank != 0){
		for(i = my_rank-1; i<number; i += p-1){
			sum += data[i];
		}
		MPI_Send(&sum, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	if(my_rank == 0){
		for(i = 1; i < p; i++){
			MPI_Recv(&sum, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
			printf("Process %d: Sum = %d\n", i, sum);
		}
		endTime = MPI_Wtime();
		printf("Time : %.5f\n", endTime - startTime);
	}

	MPI_Finalize();
}