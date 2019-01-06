#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	int my_rank, p, tag;
	double sum=0, globalsum=0;
	int intervals;
	double step, x;
	int i;
	double startTime, endTime;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	startTime = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(my_rank == 0){
		char *endP; //endpoint for strtol function
		intervals = strtol(argv[1], &endP, 10); //parsing string to long/int

		step = 1.0/(double) intervals;
		for(i=0; i<=intervals; i++){ 
			x = (i+0.5)*step;
			sum += 4.0/(1.0+x*x);
		}
		sum = step * sum;
		endTime = MPI_Wtime();
		printf("%d intervals, PI = %.15f\n", intervals, sum);
		printf("Time : %.5fs\n", endTime-startTime);
	}
	MPI_Finalize();
}