#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]){
	int my_rank, p;
	int source, dest, tag=0;
	char message[100];
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //getting processors' rank and save in variable "my_rank"
	MPI_Comm_size(MPI_COMM_WORLD, &p); //get number of processors and save into variable "p"

	if(my_rank != 0){ //If I'm not master processor
		sprintf(message, "Greetings from process %d!", my_rank); //copy message into variable "message"
		dest = 0; //destination is master processor
		MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD); //send message to master processor
	}else{
		for(source = 1; source < p; source++){ //loop and receive message from slave processors
			MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status); //receive message
			printf("%s\n", message); //print the message on console
		}
	}
	MPI_Finalize();
}