#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

struct mojaStruktura{
	int arg1, arg2, arg3;
};

void *zadanie_watku(void *arg_w)
{
	struct mojaStruktura *wskMain = arg_w;
	struct mojaStruktura struktura_lokalna;
	struktura_lokalna=*((struct mojaStruktura*)arg_w);
	printf("Watek: %d\n", pthread_self());
	printf("Wartosci przeslane: arg1=%d, arg2=%d, arg3=%d\n",
	wskMain->arg1, wskMain->arg2, wskMain->arg3);
	struktura_lokalna.arg1 = 12;
	struktura_lokalna.arg2 = -1;
	struktura_lokalna.arg3 = 123;

	printf("Lokalne wartosci: arg1=%d, arg2=%d, arg3=%d\n",
	struktura_lokalna.arg1, struktura_lokalna.arg2, struktura_lokalna.arg3);
	
	return 0;
}

int main(){
	
	pthread_t tid[2];
	struct mojaStruktura str={1,2,3};
	
	pthread_create(&tid[0], NULL, zadanie_watku, &str);
	pthread_create(&tid[1], NULL, zadanie_watku, &str);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	
	printf("Watek glowny %d\n", pthread_self());
	printf("Wartosci glowne: arg1=%d, arg2=%d, arg3=%d\n",
	str.arg1, str.arg2, str.arg3);

	return 0;
}
