#include "JsonReader.h"

void readJson(const char* fileName, Memoria *m, Processador *p, Disco *d) {
	FILE *fp;
	char *aux = (char*)malloc(sizeof(char)), *buffer = (char*)malloc(100*sizeof(char));
	struct json_object *parsed_json;
	struct json_object *memoria;
	struct json_object *cpu;
	struct json_object *disco;

	fp = fopen(fileName,"r");
    if(fp == NULL) {
        printf("Não foi possível abrir o arquivo!!\n");
    }
    while(fscanf(fp, "%c", aux) != EOF) {
        strcat(buffer, aux);
    }
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "memoria", &memoria);
	json_object_object_get_ex(parsed_json, "cpu", &cpu);
	json_object_object_get_ex(parsed_json, "disco", &disco);

    iniciaMemoria(m, json_object_get_int(memoria));
    for(int i = 0; i < json_object_get_int(cpu); i++){
        insereNoProcessador(p, NULL);
    }
    for(int i = 0; i < json_object_get_int(disco); i++){
        empilharNoDisco(d, NULL);
    }
}

void iniciaEstruturas(Memoria *m, Processador *p, Disco *d){
    iniciaProcessador(p);
    iniciaDisco(d);
    readJson("settings.json", m, p, d);
}