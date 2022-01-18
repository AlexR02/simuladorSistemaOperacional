#include "Memoria.h"

void iniciaMemoria(Memoria *h, int M){
	h->table = (Data*) malloc (M * sizeof(Data));

	for(int i=0; i<M; i++){
		h->table[i].key   = -1;
		h->table[i].processo = NULL;
		h->table[i].count = 0;
	}

	h->M = M;
}

int LRUPolicy(Memoria *h){
	int key;
	key = 0;
	for(int i=1; i<h->M; i++){
		if(h->table[i].count < h->table[key].count)
			key = i;
		h->table[i].count = 0;
	}
	//h->table[0].count = 0;
	//printf("A KEY retornada pelo LRU: %d\n", key);
	return key;
}


void insereNaMemoria(Memoria *h, Processo *processo){
	int idx = hash(processo->id, h->M);
    //printf("IDX(fora do while):%d\n", idx);
	int aux = idx;
	
	while (h->table[idx].key != -1){
        //printf("IDX:%d\n", idx);
		idx = (idx + 1) % h->M;
    	if (idx == aux){
			idx = LRUPolicy(h);
			break;
		}
	}	
	
	//printf("IDX:%d\n", idx);

	h->table[idx].key = processo->id;
	h->table[idx].processo = processo;
	h->table[idx].count = 1;
}

void imprimeHash(Memoria *h){
	for(int i=0; i<h->M; i++){
		printf("KEY:%d\t- Value:", h->table[i].key);
		printf("\n\n");
		printf("\nO valor do IDX: %d\n",hash(h->table[i].key,h->M));
		printf("\nO valor do cont: %d\n\n", h->table[i].count);
	}
}

void memInfo(Memoria *h){
	printf ("Memoria Total:%d\n", h->M);
	int aux = 0;
	if(h->table != NULL){
		if(h->table[0].processo != NULL){
			for(int i=0; i<h->M; i++){
				aux++;
			}
		}
	}
	printf("Memoria Alocada: %d\n", aux);
	printf("Memoria Livre:%d\n",h->M - aux);
}