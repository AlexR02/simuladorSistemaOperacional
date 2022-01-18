#ifndef JSONREADER_H
#define JSONREADER_H

#include <json-c/json.h>
#include <string.h>
#include "Memoria.h"
#include "Processador.h"
#include "Disco.h"
#include "Processo.h"

void readJsonEstruturas(const char* fileName, char* politica, Memoria *m, Processador *p, Disco *d);
void iniciaEstruturas(char* politica, Memoria *m, Processador *p, Disco *d);
void readJsonProcessos(const char* fileName, Processador *filaDeProcessos, char *politica, Memoria *m, Processador *p, Disco *d);
void escalonadorFIFO(Processador *filaDeProcessos, Memoria *m, Processador *cpu, Disco *d);

#endif