# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "mpi.h"
#define RANGE 10000

double calc(int id, int d){
  int i;
  double sum = 0;
    for(i = id*d ; i < (id+1)*d; i+=2){
       sum+=(1./(double)(i*2+1) - 1./(double)(i*2+3));
       }
      	return sum;
}
                  
int main ( int argc, char *argv[] )
{
  int tag = 1;
  int id,p,i,range;  
  MPI_Status status;
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &id );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  for(range = RANGE ;range<=1000000000; range*=10){
	  int d = range/p;
	  double sum = 0;
	  sum =calc(id,d);
	  if(id!=0)
	      MPI_Send ( &sum, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD );
		printf("PROCES_ID: %d PI: %lf, MATH-PI: %lf, ERROR: %lf\n",id, sum,M_PI,M_PI-sum); 
	 if(id==0)
		{
	 	 printf("Dokładność: %d\n",range);
		  double item = 0;
		  for(i = 1; i<p;i++){
		    MPI_Recv ( &item, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status );
		    sum+=item;
		  }
		  sum*=4;
		  printf("PI: %lf, MATH-PI: %lf, ERROR: %lf\n",sum,M_PI,M_PI-sum);
		}
  }
  MPI_Finalize ( );
  return 0;
}
