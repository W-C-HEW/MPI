#include <stdio.h>
#include <stdlib.h> //for malloc
#include <mpi.h>

int main(int argc, char* argv[]){
	int my_rank, p;
	int number;
	int *data=NULL;
	int *dataArr;
	int sum=0, totalSum=0;
	int i;
	int* toSum;
	char* endPoint;
	double startTime, endTime;

	MPI_Init(&argc, &argv);
	startTime = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	number = strtol(argv[1], &endPoint, 10); 

	if(my_rank == 0){
		data = malloc(number*sizeof(int)); //allocate memory
		for(i=1; i<=number; i++) //initialize data
			data[i-1]=i;
	}

	toSum = malloc(number/p*sizeof(int));


	MPI_Scatter(data, number/p, MPI_INT, toSum, number/p, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(i=0; i<number/p; i++){
		sum += toSum[i];
	}
	dataArr = malloc(p*sizeof(int));

	MPI_Gather(&sum, 1, MPI_INT, dataArr, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if(my_rank == 0){
		for(i=0; i<p; i++){
			totalSum += dataArr[i];
		}
		printf("Total : %d\n", totalSum);
		endTime = MPI_Wtime();
		printf("Time : %.5fs\n", endTime-startTime);
	}
	MPI_Finalize();
}