#ifndef DISCO_H
#define DISCO_H

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"

typedef struct Disco Disco;
typedef struct TipoBloco_pilha Bloco_pilha;
typedef struct VetorDisco VetorDisco;

struct TipoBloco_pilha{
    Processo *processo;
    Bloco_pilha *proximo;
};

struct Disco{
    Bloco_pilha *top;
    int tam;
};

void iniciaDisco(Disco *disco);
void empilharNoDisco(Disco *disco, Processo *processo);
void desempilhar(Disco *disco, Processo *processo);
void desempilharTodos(Disco *disco);
int tamanho(Disco disco);
void imprimeDisco(Disco *disco);
int buscarElemento(Disco *disco, int i);

#endif