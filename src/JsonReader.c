#include "JsonReader.h"
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void readJsonEstruturas(const char* fileName, char* politica, Memoria *m, Processador *p, Disco *d) {
	FILE *fp;
	char *aux = (char*)malloc(sizeof(char)), *buffer = (char*)malloc(100*sizeof(char));
	struct json_object *parsed_json;
	struct json_object *memoria;
	struct json_object *cpu;
	struct json_object *disco;
    struct json_object *politicaJson;

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
    json_object_object_get_ex(parsed_json, "politica", &politicaJson);

    iniciaMemoria(m, json_object_get_int(memoria));
    p->tam = json_object_get_int(cpu);
    for(int i = 0; i < json_object_get_int(cpu); i++){
        insereNoProcessador(p, NULL);
    }
    for(int i = 0; i < json_object_get_int(disco); i++){
        empilharNoDisco(d, NULL);
    }
    
    strcpy(politica, json_object_get_string(politicaJson));
}

void iniciaEstruturas(char* politica, Memoria *m, Processador *p, Disco *d){
    iniciaProcessador(p);
    iniciaDisco(d);
    readJsonEstruturas("settings.json", politica, m, p, d);
}

void readJsonProcessos(const char* fileName, Processador *filaDeProcessos, char *politica, Memoria *m, Processador *p, Disco *d) {
    FILE *fp;
	size_t len = 100;
    char *buffer = (char*)malloc(100*sizeof(char));
    iniciaProcessador(filaDeProcessos);
    struct json_object *parsed_json;
	struct json_object *processo;
	struct json_object *ciclos;
	struct json_object *max_quantum;
    struct json_object *init_type;
    struct json_object *timestamp;
    struct json_object *prioridade;

	fp = fopen(fileName,"r");
    if(fp == NULL) {
        printf("Não foi possível abrir o arquivo!!\n");
    }
    int aux = 0;
    while(getline(&buffer, &len, fp) > 0) {
        Processo *p = (Processo*)malloc(sizeof (Processo));
        parsed_json = json_tokener_parse(buffer);

        json_object_object_get_ex(parsed_json, "processo", &processo);
        json_object_object_get_ex(parsed_json, "ciclos", &ciclos);
        json_object_object_get_ex(parsed_json, "max_quantum", &max_quantum);
        json_object_object_get_ex(parsed_json, "init_type", &init_type);
        json_object_object_get_ex(parsed_json, "timestamp", &timestamp);
        json_object_object_get_ex(parsed_json, "prioridade", &prioridade);

        p->id = json_object_get_int(processo);
        p->ciclos = json_object_get_int(ciclos);
        p->max_quantum = json_object_get_int(max_quantum);
        p->init_type = (char*)malloc(sizeof (char));
        strcpy(p->init_type, json_object_get_string(init_type));
        p->timestamp = json_object_get_int(timestamp);
        p->prioridade = json_object_get_int(prioridade);
        filaDeProcessos->tam++;
        p->status = (char*)malloc(sizeof(char));
        insereNoProcessador(filaDeProcessos, p); 
        aux = 1;    
    }

    if(aux == 1){
        printf("\nPROCESSOS CARREGADOS NO SISTEMA COM SUCESSO!!\n");
        fclose(fp);

        if(strcmp(politica, "FIFO") == 0){
            escalonadorFIFO(filaDeProcessos, m, p, d);
        }
    }else if(aux == 0){
        printf("O arquivo com os processos está vazio!!\n");
    }
}

void escalonadorFIFO(Processador *filaDeProcessos, Memoria *m, Processador *cpu, Disco *d){

    FILE *resultados;
    resultados = fopen("resultados.txt", "w");
    if(resultados == NULL) {
        printf("Não foi possível criar o arquivo para escrever os resultados!!\n");
    }
    
    BlocoLista *b = filaDeProcessos->primeiro;
    if(filaDeProcessos->primeiro == filaDeProcessos->ultimo){
        printf("Não existem processos na fila\n");
        return;
    }

    int aux = 0; //auxiliar para saber quantos processos já se encerraram
    int ciclo = 1; //quantidades de cilos corridos
    int auxCiclo = 0;

    while((filaDeProcessos->cont - aux) != 0){
        b = b->proximo;
        Processo *p = b == NULL ? NULL : b->processo;
        if(ciclo != auxCiclo){
            fprintf(resultados,"%s %d \n","PROCESSOS QUE RODARAM NO CICLO ", ciclo);
        }

        if(p != NULL){
            auxCiclo = ciclo;
            insereNoProcessador(cpu, p);
            if(strcmp(p->init_type, "cpu-bound") == 0 && p->ciclos > 0){
                strcpy(p->status,"executando");
                sleep(p->max_quantum);
                p->ciclos--;
                p->timestamp = p->timestamp + p->max_quantum;
                if(p->ciclos == 0){
                    strcpy(p->status,"pronto");
                    aux++;
                }
                removeDoProcessador(cpu, cpu->primeiro);
                fprintf(resultados,"\t%s %d%s %d%s %s\n","ID:", p->id, "; TIMESTAMP:", p->timestamp, "; TYPE:", p->init_type);
            }else if(p->ciclos > 0){
                srand((unsigned)time(NULL));
                removeDoProcessador(cpu, cpu->primeiro);
                if(strcmp(p->init_type, "io-bound") == 0){
                    strcpy(p->status,"bloqueado");
                    sleep(1 + (rand() % 4));//punição do processo
                    p->timestamp = p->timestamp + 1 + (rand() % 4);
                    empilharNoDisco(d, p);
                    strcpy(p->status,"executando");
                    sleep(p->max_quantum);
                    p->ciclos--;
                    p->timestamp = p->timestamp + p->max_quantum;
                    if(p->ciclos == 0){
                        strcpy(p->status,"pronto");
                        aux++;
                    }
                    fprintf(resultados,"\t%s %d%s %d%s %s\n","ID:", p->id, "; TIMESTAMP:", p->timestamp, "; TYPE:", p->init_type);
                }else if(strcmp(p->init_type, "memory-bound") == 0){
                    strcpy(p->status,"bloqueado");
                    sleep(1 + (rand() % 4));//punição do processo
                    p->timestamp = p->timestamp + 1 + (rand() % 4);
                    insereNaMemoria(m, p);
                    strcpy(p->status,"executando");
                    sleep(p->max_quantum);
                    p->ciclos--;
                    p->timestamp = p->timestamp + p->max_quantum;
                    if(p->ciclos == 0){
                        strcpy(p->status,"pronto");
                        aux++;
                    }
                    fprintf(resultados,"\t%s %d%s %d%s %s\n","ID:", p->id, "; TIMESTAMP:", p->timestamp, "; TYPE:", p->init_type);
                }
            }
        }else{
            b = filaDeProcessos->primeiro;
            ciclo++;
            fprintf(resultados,"\n\n");
        }
    }
    printf("Terminou o load dos processos\n");
    fclose(resultados);
}