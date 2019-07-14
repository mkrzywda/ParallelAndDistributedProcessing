#include<stdlib.h>
#include <stdio.h>
#include<pthread.h>

int zmienna_wspolna=0;

void *zadanie_watku(void *arg_w){
	int id = pthread_self();
	printf("id systemowy: %u przeslany identyfikator: %d\n", id, arg_w);
}

int main(){
	pthread_t tid[5];
	void *wynik;
	int id[5];
	int i;
	
	for(i=0; i<5; i++){
		id[i] = i;
		pthread_create(&tid[i], NULL, zadanie_watku, (void*)&id[i]);
			
	}

	for(i=0; i<5; i++){
		pthread_join(tid[i], &wynik);
	}
	
	exit(0);
}


