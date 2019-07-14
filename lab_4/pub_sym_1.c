#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>

int l_kf, l_kr;

pthread_mutex_t mutex;

void * watek_klient (void * arg);

main(){

  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, i;

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);

  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  l_kr = 1;

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;


  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
  printf("\nZamykamy pub!\n");


}


void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);

  int i, j, kufel, result;
  int ile_musze_wypic = 2;

  printf("\nKlient %d, wchodzę do pubu\n", moj_id); 
    
  for(i=0; i<ile_musze_wypic; i++){
	    
	int sukces = 0;
	while(sukces == 0){
		pthread_mutex_lock(&mutex);
		if(l_kf > 0){
			sukces = 1;
			printf("\nKlient %d, wybieram kufel\n", moj_id); 
			printf("Liczba dostepnych kufli po zabraniu: %d => %d\n", l_kf, l_kf - 1);
			l_kf--;
		}
		else{
			printf("\nKlient %d: brak wolnych kufli! %d\n , Ide robic coś innego", moj_id);
			printf(" Liczba dostepnych kufli: %d\n", l_kf);
		}
		pthread_mutex_unlock(&mutex);
		nanosleep((struct timespec[]){{0, 500000000L}}, NULL);
	}
    pthread_mutex_lock(&mutex);
    j=0;
    printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j); 
    nanosleep((struct timespec[]){{0, 500000000L}}, NULL);
    pthread_mutex_unlock(&mutex);    

    printf("\nKlient %d, pije\n", moj_id); 
    nanosleep((struct timespec[]){{0, 500000000L}}, NULL);
    
    pthread_mutex_lock(&mutex);    
    printf("\nKlient %d, odkladam kufel\n", moj_id); 
    printf(" Liczba dostepnych kufli po odlozeniu: %d => %d\n", l_kf, l_kf + 1);
    l_kf++; 
    sukces = 0;
    pthread_mutex_unlock(&mutex);
  }

  printf("\nKlient %d, wychodzę z pubu\n", moj_id); 
    
  return(NULL);
} 


