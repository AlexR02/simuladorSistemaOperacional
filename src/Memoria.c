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


void insereNaMemoria(Memoria *h, int key, Processo *processo){
	int idx = hash(key, h->M);
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

	h->table[idx].key   = key;
	h->table[idx].processo = processo;
	h->table[idx].count = 1;
}