#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Processo Processo;

struct Processo{
	int id;
    char *descricao;
	int timestamp; 
    int quantum;
};

void processo(int id, char* descricao, int timestamp, int quantum);
void imprimeProcesso(Processo p);

#endif