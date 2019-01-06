#include <stdio.h>
#include <stdlib.h> //for malloc
#include <mpi.h>

int main(int argc, char* argv[]){
	int my_rank, p;
	int number;
	int *data=NULL;
	int *localdata;
	int *toSum;
	int sum=0;
	int i;
	char* endPoint;
	double startTime, endTime;

	MPI_Init(&argc, &argv);
	startTime = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	number = strtol(argv[1], &endPoint, 10); 
	toSum = malloc(5*sizeof(int));

	if(my_rank == 0){
		data = malloc(number*sizeof(int)); //allocate memory
		for(i=1; i<=number; i++) //initialize data
			data[i-1]=i;
	}

	
	MPI_Scatter(data, 5, MPI_INT, &toSum, 5, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(i=0; i<5; i++){
		printf("Process %d: %d %d %d %d %d\n", my_rank, toSum[0], toSum[1], toSum[2], toSum[3], toSum[4]);
	}


	//MPI_Gather(&sum, 1, MPI_INT, sumData, 1, MPI_INT, 0, MPI_COMM_WORLD);
	endTime = MPI_Wtime();
	//printf("Time : %.5fs\n", endTime-startTime);

	MPI_Finalize();
}