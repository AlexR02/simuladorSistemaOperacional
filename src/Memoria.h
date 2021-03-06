#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"

#define hash(v, M) (v % M)

typedef struct DataTable Data;
typedef struct Memoria Memoria;


struct DataTable{
	int key;
    Processo *processo;
	int count; //necessário apenas para a política LRU
	int segments;
};


struct Memoria{
	Data *table;
	int M;
	int count;
	int *blocosSegmentos;
};

void iniciaMemoria(Memoria *h, int M);
void imprimeMemoria(Memoria *h);
int getValueMemoria(Memoria *h, int key);
int LRUPolicy(Memoria *h);
void insereNaMemoria(Memoria *h, Processo *processo, int segments);
void removeDaMemoria(Memoria *h, int key);
void memInfo(Memoria *h);
void imprimeHash(Memoria *h);

#endif