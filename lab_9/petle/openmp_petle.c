#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifdef _OPENMP
	#include <omp.h>
#endif

#define WYMIAR 4

int main()
{
	double a[WYMIAR][WYMIAR];
	int i, j;
	
	for ( i = 0; i < WYMIAR; i++ )
		for ( j = 0; j < WYMIAR; j++ )
			a[i][j] = 1.02*i + 1.01*j;
	
	double suma = 0.0;
	
	for ( i = 0; i < WYMIAR; i++ )
		for ( j = 0; j < WYMIAR; j++ )
			suma += a[i][j];
	
	printf( "\nSUMA SEKWENCYJNIE= %lf\n", suma );
	
	omp_set_nested(1);
	int number_of_threads = 3;
	omp_set_num_threads(number_of_threads);
	double suma_p;
	int id;	
	
	
	printf( "\nWIERSZOWO ZEWNETRZNIE\n" );
	suma_p = 0.0;
	
	//#pragma omp parallel for ordered schedule(static, 3) private(j) reduction(+ : suma_p)
	//#pragma omp parallel for ordered schedule(static) private(j) reduction(+ : suma_p)
	//#pragma omp parallel for ordered schedule(dynamic, 2) private(j) reduction(+ : suma_p)
	#pragma omp parallel for ordered schedule(dynamic) private(j) reduction(+ : suma_p)
	for ( i = 0; i < WYMIAR; i++ )
	{
		id = omp_get_thread_num();
		for ( j = 0; j < WYMIAR; j++ )
		{
			suma_p += a[i][j];
			#pragma omp ordered
			printf( "(%2d, %2d) - W(%1d, %1d)", i, j, id, omp_get_thread_num() );
		}
		printf("\n");
	}
	printf( "SUMA WIERSZOWO ZEWNETRZNIE= %lf\n", suma_p );
	
	printf( "\nWIERSZOWO WEWNETRZNIE\n" );
	suma_p = 0.0;
	double *tab_sum = malloc(sizeof *tab_sum * number_of_threads);
	for ( i = 0; i < number_of_threads; i++ )//tablica do sumowania
		tab_sum[i] = 0.0;
	
	int k;
	
	for ( i = 0; i < WYMIAR; i++ )
	{
		id = omp_get_thread_num();
		
		//#pragma omp parallel for ordered schedule(static, 3) firstprivate(i) num_threads(3)
		//#pragma omp parallel for ordered schedule(static) firstprivate(i) num_threads(3)
		//#pragma omp parallel for ordered schedule(dynamic, 2) firstprivate(i) num_threads(3)
		#pragma omp parallel for ordered schedule(dynamic) firstprivate(i) num_threads(3)
		for ( j = 0; j < WYMIAR; j++ )
		{
			tab_sum[omp_get_thread_num()] += a[i][j];
			#pragma omp ordered
			printf( "(%2d, %2d) - W(%1d, %1d)", i, j, id, omp_get_thread_num() );
		}
		printf("\n");
	}
	
	for ( k = 0; k < number_of_threads; k++ )
			suma_p += tab_sum[k];
	
	printf( "SUMA WIERSZOWO WEWNETRZNIE = %lf\n", suma_p );

	
	printf( "\nKOLUMNOWO WEWNETRZNIE\n" );
	suma_p = 0.0;
	for ( j = 0; j < WYMIAR; j++ )
	{
		id = omp_get_thread_num();
		
		//#pragma omp parallel for ordered schedule(static, 3) firstprivate(j) reduction(+ : suma_p)
		//#pragma omp parallel for ordered schedule(static) firstprivate(j) reduction(+ : suma_p)
		//#pragma omp parallel for ordered schedule(dynamic, 2) firstprivate(j) reduction(+ : suma_p)
		#pragma omp parallel for ordered schedule(dynamic) firstprivate(j) reduction(+ : suma_p)
		for ( i = 0; i < WYMIAR; i++ )
		{
			suma_p += a[i][j];
			#pragma omp ordered
			printf( "(%2d, %2d) - W(%1d, %1d)", i, j, id, omp_get_thread_num() );
		}
		printf("\n");
	}
	printf( "SUMA OLUMNOWO WEWNETRZNIE = %lf\n", suma_p );
	
	
	
	printf( "\nKOLUMNOWO ZEWNETRZNIE\n" );
	suma_p = 0.0;
	double suma_k = 0.0;
	
	//#pragma omp parallel for ordered schedule(static, 3) private(i, suma_p)
	//#pragma omp parallel for ordered schedule(static) private(i, suma_p)
	//#pragma omp parallel for ordered schedule(dynamic, 2) private(i, suma_p)
	#pragma omp parallel for ordered schedule(dynamic) private(i, suma_p)
	for ( j = 0; j < WYMIAR; j++ )
	{
		suma_p = 0.0;
		id = omp_get_thread_num();
		for ( i = 0; i < WYMIAR; i++ )
		{
			suma_p += a[i][j];
			#pragma omp ordered
			printf( "(%2d, %2d) - W(%1d, %1d)", i, j, id, omp_get_thread_num() );
		}
		
		#pragma omp critical
		{
			suma_k += suma_p;
		}
		printf("\n");
	}
	printf( "SUMA KOLUMNOWO ZEWNETRZNIE = %lf\n", suma_k );
	
	
	
	printf( "\nPODZIAL BLOKOWY \n" );
	suma_p = 0.0;
	#pragma omp parallel for ordered schedule(static) reduction(+ : suma_p) num_threads(3)
	//pragma omp parallel for ordered schedule(static,2) reduction(+ : suma_p) num_threads(3)
	//pragma omp parallel for ordered schedule(static) reduction(+ : suma_p) num_threads(3)
	for ( i = 0; i < WYMIAR; i++ )
	{
		id = omp_get_thread_num();
		
		#pragma omp ordered
		{
			#pragma omp parallel for ordered schedule(static,1) firstprivate(i) reduction(+ : suma_p) num_threads(4)
			//#pragma omp parallel for ordered schedule(static,2) firstprivate(i) reduction(+ : suma_p) num_threads(4)
			//#pragma omp parallel for ordered schedule(static) firstprivate(i) reduction(+ : suma_p) num_threads(4)
			for ( j = 0; j < WYMIAR; j++ )
			{
				suma_p += a[i][j];
				#pragma omp ordered 
				printf( "(%2d, %2d) - W(%1d, %1d)", i, j, id, omp_get_thread_num() );
			}
		}
		printf("\n");
	}
	printf( "SUMA DLA PODZIALU BLOKOWEGO = %lf\n", suma_p );
	
}
