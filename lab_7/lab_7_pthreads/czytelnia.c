#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"

int my_read_lock_lock(czytelnia_t* czytelnia_p){
	pthread_mutex_lock(&czytelnia_p->czytelnicy_mutex);
	
	if ( czytelnia_p->liczba_pis > 0 )
		pthread_cond_wait(&czytelnia_p->czytelnicy_condition, &czytelnia_p->czytelnicy_mutex);
	
	czytelnia_p->liczba_czyt++;
	pthread_mutex_unlock(&czytelnia_p->czytelnicy_mutex);
	pthread_cond_signal(&czytelnia_p->czytelnicy_condition);
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->czytelnicy_mutex);
	
	czytelnia_p->liczba_czyt--;
	
	pthread_mutex_unlock(&czytelnia_p->czytelnicy_mutex);

	if (czytelnia_p->liczba_czyt == 0)
		pthread_cond_signal(&czytelnia_p->pisarze_condition);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
	pthread_mutex_lock(&czytelnia_p->pisarze_mutex);
	
	if ( ((czytelnia_p->liczba_pis) + (czytelnia_p->liczba_czyt)) > 0 )
		pthread_cond_wait(&czytelnia_p->pisarze_condition, &czytelnia_p->pisarze_mutex);	
	
	czytelnia_p->liczba_pis++;
		
	pthread_mutex_unlock(&czytelnia_p->pisarze_mutex);
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->pisarze_mutex);
	
	czytelnia_p->liczba_pis--;
	
	pthread_mutex_unlock(&czytelnia_p->pisarze_mutex);
	pthread_cond_signal(&czytelnia_p->czytelnicy_condition);
}

void inicjuj(czytelnia_t* czytelnia_p){
	pthread_cond_init( &czytelnia_p->czytelnicy_condition, NULL );
	pthread_cond_init( &czytelnia_p->pisarze_condition, NULL );
	czytelnia_p->liczba_pis = 0;
	czytelnia_p->liczba_czyt = 0;
	pthread_mutex_init(&czytelnia_p->czytelnicy_mutex, NULL);
	pthread_mutex_init(&czytelnia_p->pisarze_mutex, NULL);
}

void czytam(czytelnia_t* czytelnia_p){
	printf("\nILE CZYTA: %d", czytelnia_p->liczba_czyt);
	printf("\nILE PISZE: %d\n", czytelnia_p->liczba_pis);
   if ( (czytelnia_p->liczba_czyt > 0) && (czytelnia_p->liczba_pis == 0) )
		usleep(rand()%1000000);
	else
		printf("KOMUNIKAT BLEDU CZYTANIA");
}

void pisze(czytelnia_t* czytelnia_p){
	printf("\nILE CZYTA: %d", czytelnia_p->liczba_czyt);
	printf("\nILE PISZE: %d\n", czytelnia_p->liczba_pis);
    if ( (czytelnia_p->liczba_czyt == 0) && (czytelnia_p->liczba_pis == 1) )
		usleep(rand()%1000000);
	else
		printf("KOMUNIKAT BLEDU PISANIA");
}


