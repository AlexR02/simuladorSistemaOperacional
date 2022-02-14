#include "Memoria.h"

void iniciaMemoria(Memoria *h, int M){
	h->table = (Data*) malloc (M * sizeof(Data));

	for(int i=0; i<M; i++){
		h->table[i].key   = -1;
		h->table[i].processo = NULL;
		h->table[i].count = 0;
		h->table[i].segments = 0;
	}

	h->M = M;
	h->blocosSegmentos = (int*)malloc(M*sizeof(int));
	for(int i=0;i<M;i++){
		h->blocosSegmentos[i] = 0;
	}
	h->count = 0;
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


void insereNaMemoria(Memoria *h, Processo *processo, int segments){
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
	h->table[idx].segments = segments;
}

void removeDaMemoria(Memoria *h, int key){
	int idx = hash(key, h->M);

	if(h->table[idx].key == key){
		h->table[idx].key = -1;
		h->table[idx].processo = NULL;
		h->table[idx].count = 0;
		int aux = 0;
		for(int i = 0; i < h->M; i++){
			if(h->blocosSegmentos[i] == key){
				h->blocosSegmentos[i] = 0;
				h->count--;
				aux++;
				if(aux == h->table[idx].segments){
					break;
				}
			}
		}
		h->table[idx].segments = 0;
	}
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
	printf("Dê um 'enter' para parar o monitoramento!!\n");
	printf("Segmento Total da Memória: %d\n", h->M);
	printf("Alocação dos segmentos da memória: ");
	for(int i=0;i<h->M;i++){
		printf("%d ", h->blocosSegmentos[i]);
	}
	printf("\n");
	printf("Segmentos Alocados da Memória: %d\n", h->count);
	printf("Segmentos Livres da Memória: %d\n",h->M - h->count);
}