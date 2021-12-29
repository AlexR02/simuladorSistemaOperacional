#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"

typedef struct TipoBlocoLista BlocoLista;
typedef struct TipoLista Processador;

struct TipoBlocoLista{
    Processo *processo;
    BlocoLista *proximo;
};

struct TipoLista{
    BlocoLista *primeiro;
    BlocoLista *ultimo;
    int cont;
};

void iniciaProcessador(Processador *lista);
void insereNoProcessador(Processador *lista, Processo *processo);
void removeDoProcessador(Processador *lista, BlocoLista *b, Processo *processo);
void cpuInfo(Processador *lista);

#endif