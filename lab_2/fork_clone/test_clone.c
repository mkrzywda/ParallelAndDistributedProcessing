#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{

  
   int w = (int) (*((int*) argument));
   int i;

  	for (i=0 ;i<333 ;i++) {
	zmienna_globalna++;
	w++;
	}
   
  return 0;
}

main()
{

  void *stos, *stos2;
  pid_t pid, pid2;
  int i = 0; 
  
  inicjuj_czas();
  stos = malloc( ROZMIAR_STOSU );
  stos2 = malloc( ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
 
  if (stos2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }

 

    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void*)&i);
   
    pid2 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void*)&i);

   
    
waitpid(pid, NULL, __WCLONE);
waitpid(pid2, NULL, __WCLONE);
  

  drukuj_czas();
	printf("zmienna global = %d",zmienna_globalna);
	printf("\n zmienna = %d",i);

  free( stos );
  free( stos2 );
 
}
