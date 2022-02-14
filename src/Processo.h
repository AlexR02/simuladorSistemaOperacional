#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Processo Processo;

struct Processo{
	int id;
    double ciclos;
    double ciclosTotais;
    double cliclosAux;
	double max_quantum; 
    char *init_type;
    int timestamp;
    int prioridade;
    char *status;
    int bilhetes;
    int qtdBloq;
};

//void processo(int id, int ciclos, int max_quantum, char *init_type, int timestamp, int prioridade);
void imprimeProcesso(Processo p);

#endif