#ifndef JSONREADER_H
#define JSONREADER_H

#include <json-c/json.h>
#include "Memoria.h"
#include "Processador.h"
#include "Disco.h"

void readJson(const char* fileName, Memoria *m, Processador *p, Disco *d);
void iniciaEstruturas(Memoria *m, Processador *p, Disco *d);

#endif