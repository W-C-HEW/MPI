#include <stdio.h>
#include <stdlib.h> //for malloc
#include <mpi.h>

int main(int argc, char* argv[]){
	int my_rank, p;
	int number;
	int *data=NULL;
	int sum=0;
	int i;
	char* endPoint;
	double startTime, endTime;

	MPI_Init(&argc, &argv);
	startTime = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(my_rank == 0){
		number = strtol(argv[1], &endPoint, 10);
		data = malloc(number*sizeof(int)); //allocate memory
		for(i=1; i<=number; i++) 
			data[i-1]=i;
		for(i=0; i<number; i++)
			sum += data[i];
		printf("Process %d : Sum = %d\n", my_rank, sum);
		endTime = MPI_Wtime();
		printf("Time : %.5fs\n", endTime-startTime);
	}

	MPI_Finalize();
}