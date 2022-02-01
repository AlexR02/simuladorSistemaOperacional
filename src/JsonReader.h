#ifndef JSONREADER_H
#define JSONREADER_H

#include <json-c/json.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "Memoria.h"
#include "Processador.h"
#include "Disco.h"
#include "Processo.h"

void readJsonEstruturas(const char* fileName, char* politica, Memoria *m, Processador *p, Disco *d);
void iniciaEstruturas(char* politica, Memoria *m, Processador *p, Disco *d);
void readJsonProcessos(const char* fileName, Processador *filaDeProcessos);
void executeProcessos();
void manipulaProcesso();
void* escalonadorFIFOandLRU();
void sortProcess(Processador *l);
void* testThread();
void *escalonadorMFP();
void separaProcessosPrioridade(Processador *l, int prioridade);
void manipulaProcessoMFP(Processador *atual, Processador *futura);
void sortProcessBilhetes(Processador *l);
void sorteiaBilhetes(int idExecutado);

#endif