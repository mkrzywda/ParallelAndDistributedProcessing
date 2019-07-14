#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
	pthread_rwlock_rdlock(&rwlock);
	czytelnia_p->liczba_czyt++;
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
	czytelnia_p->liczba_czyt--;
	pthread_rwlock_unlock(&rwlock);
	pthread_rwlock_unlock(&rwlock);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
	pthread_rwlock_wrlock(&rwlock);	
	czytelnia_p->liczba_pis++;
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    czytelnia_p->liczba_pis--;
	pthread_rwlock_unlock(&rwlock);
}

void inicjuj(czytelnia_t* czytelnia_p){
	czytelnia_p->liczba_pis = 0;
	czytelnia_p->liczba_czyt = 0;
}

void czytam(czytelnia_t* czytelnia_p){
	printf("\nLiczba czytelnikow: %d", czytelnia_p->liczba_czyt);
	printf("\nLiczba pisarzy: %d\n", czytelnia_p->liczba_pis);
    if ( (czytelnia_p->liczba_czyt > 0) && (czytelnia_p->liczba_pis == 0) )
		usleep(rand()%1000000);
	else
		printf("KOMUNIKAT BLEDU CZYTANIA");
}

void pisze(czytelnia_t* czytelnia_p){
	printf("\nLiczba czytelnikow: %d", czytelnia_p->liczba_czyt);
	printf("\nLiczba pisarzy: %d\n", czytelnia_p->liczba_pis);
    if ( (czytelnia_p->liczba_czyt == 0) && (czytelnia_p->liczba_pis == 1) )
		usleep(rand()%1000000);
	else
		printf("KOMUNIKAT BLEDU PISANIA");
}


