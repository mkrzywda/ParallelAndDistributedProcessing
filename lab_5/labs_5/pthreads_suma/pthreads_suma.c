#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<math.h>

#define ROZMIAR 100000000 
#define LICZBA_W 17

pthread_mutex_t muteks; 
pthread_t watki[LICZBA_W];
double global_array_of_local_sums[LICZBA_W];


void *suma_w( void *arg_wsk);
void *suma_w_no_mutex( void *arg_wsk);
void *calka( void *arg_wsk);


struct zas{
	
	double a; 
	double b;
	};
	
struct zas globalny_zas[ROZMIAR];

double *tab;
double suma=0; 

int main( int argc, char *argv[] ){
  int i;
    double t1,t2,t3;

    t1 = czas_zegara();
    double f(double x){
        return sin(x);
    }

    double a = -M_PI; 
    double b = M_PI;
    double x1 = a;
    double x2;
    double dx = (b-a)/ROZMIAR;
    double c = 0.0;

    for (i = 0; i < ROZMIAR; i++){
        x2 = x1 + dx;
        c += (f(x1)+f(x2));
        x1 = x2;
    }
    c *= 0.5*dx;
    
    t1 = czas_zegara() - t1;
    printf("\nINTEGRAL FROM TASK 3\nRESULT INTEGRAL : %.12lf\n", c);
	printf("TIME = %.8lf\n", t1);
    x1 = a;
    dx = (b-a) / LICZBA_W;
    for (i = 0; i < LICZBA_W; i++){
        x2 = x1 + dx;
        globalny_zas[i].a = x1;
        globalny_zas[i].b = x2;
        x1 = x2;
    }
    
    printf("\n\n");
  int indeksy[LICZBA_W]; 
  for(i=0;i<LICZBA_W;i++) indeksy[i]=i;
  tab = (double *) malloc(ROZMIAR*sizeof(double));
  for(i=0; i<ROZMIAR; i++ ) tab[i] = ((double) i+1) / ROZMIAR; 
  pthread_mutex_init( &muteks, NULL);

  t1 = czas_zegara();
  for(i=0; i<LICZBA_W; i++ ) pthread_create( &watki[i], NULL, calka, (void *) &globalny_zas[i] );

  for(i=0; i<LICZBA_W; i++ ) pthread_join( watki[i], NULL );

  t1 = czas_zegara() - t1;
  printf("INTEGRAL FROM TASK 4 \nRESULT INTEGRAL : %.12lf\n", suma);
  printf("TIME = %.8lf\n", t1);
  
  printf("\n\n");
  suma =0;
  t1 = czas_zegara();

  for(i=0; i<LICZBA_W; i++ ) {
    global_array_of_local_sums[i]=0.0;
    pthread_create( &watki[i], NULL, calka, (void *) &globalny_zas[i] );
  }

  for(i=0; i<LICZBA_W; i++ ) pthread_join( watki[i], NULL );

  t1 = czas_zegara() - t1;
  printf("INTEGRAL FROM TASK 5 \nRESULT INTEGRAL : %.12lf\n", suma);
  printf("TIME = %.8lf\n", t1);

  printf("\n\n");
  
 
  
}

void *suma_w( void *arg_wsk){

  int i, j, moj_id;

  double moja_suma=0;

  moj_id = *( (int *) arg_wsk ); 

  j=ROZMIAR/LICZBA_W;
  for( i=j*moj_id+1; i<=j*(moj_id+1); i++){ 
    moja_suma += tab[i]; 
  }

  pthread_mutex_lock( &muteks );
  suma += moja_suma;
  pthread_mutex_unlock( &muteks );

  pthread_exit( (void *)0);

}
void *suma_w_no_mutex( void *arg_wsk){

  int i, j, moj_id;

  moj_id = *( (int *) arg_wsk ); 

  j=ROZMIAR/LICZBA_W;
  for( i=j*moj_id+1; i<=j*(moj_id+1); i++){ 
    global_array_of_local_sums[moj_id] += tab[i]; 
  }

  pthread_exit( (void *)0);

}

void *calka(void *arg_wsk){
	
    struct zas z;
    z = *((struct zas *) arg_wsk);
    int ile = ROZMIAR/LICZBA_W;
    double x1 = z.a;
    double x2;
    double c =0.0;
    double f(double x){
        return sin(x);
    }
    double dx = (z.b - z.a) / ile;
    int i;
    for (i = 0; i < ile; i++){
        x2 = x1 + dx;
        c += (f(x1)+f(x2));
        x1 = x2;
        
    }
    c *= 0.5*dx;
    
  pthread_mutex_lock( &muteks );
  suma += c;
  pthread_mutex_unlock( &muteks );
  pthread_exit( (void *)0);
}
