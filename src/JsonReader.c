#include "JsonReader.h"

int auxDoneProcess = 0; //auxiliar para saber quantos processos já se encerraram
int qtdCiclos = 1; //quantidades de cilos corridos
int auxQtdCiclo = 0;
FILE *resultados;
char types[3][15] = {"cpu-bound", "memory-bound", "io-bound"}; 
//Processador *filaDeProcessos, char *politica, Memoria *m, Processador *p, Disco *d)
Processador *filaDeProcessosG;
char *politicaG;
Memoria *mG;
Processador *pG;
Disco *dG;
Processo *pAuxG;

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
    
    pG = (Processador*)malloc(sizeof (Processador));
    pG = p;

    mG = (Memoria*)malloc(sizeof (Memoria));
    mG = m;

    dG = (Disco*)malloc(sizeof (Disco));
    dG = d;

    politicaG = (char*)malloc(sizeof (char));
    strcpy(politicaG, politica);
}

void iniciaEstruturas(char* politica, Memoria *m, Processador *p, Disco *d){
    iniciaProcessador(p);
    iniciaDisco(d);
    readJsonEstruturas("settings.json", politica, m, p, d);
}

void readJsonProcessos(const char* fileName, Processador *filaDeProcessos) {
    
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
        p->ciclos = json_object_get_double(ciclos);
        p->ciclosTotais = json_object_get_double(ciclos);
        p->max_quantum = json_object_get_int(max_quantum);
        p->init_type = (char*)malloc(sizeof (char));
        strcpy(p->init_type, json_object_get_string(init_type));
        p->timestamp = json_object_get_int(timestamp);
        p->prioridade = json_object_get_int(prioridade);
        filaDeProcessos->tam++;
        p->status = (char*)malloc(sizeof(char));
        p->bilhetes = 0;
        strcpy(p->status,"pronto");
        insereNoProcessador(filaDeProcessos, p); 
        aux = 1;    
    }
    
    if(aux == 1){
        printf("Os processos foram carregados com sucesso!!\n");
        filaDeProcessosG = (Processador*)malloc(sizeof (Processador));
        filaDeProcessosG = filaDeProcessos;
    }else if(aux == 0){
        printf("O arquivo com os processos está vazio!!\n");
    }
}

//Acrescentando texto para marcar esse como o ponto em que tudo ainda funciona!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void executeProcessos() {

    if(filaDeProcessosG->primeiro == filaDeProcessosG->ultimo){
        printf("Não existem processos na fila\n");
        return;
    }

    if(strcmp(politicaG, "FIFO") == 0 || strcmp(politicaG, "LRU") == 0){
        printf("Iniciando escalonamento dos processos em modo %s\n", politicaG);
        printf("Utilize o comando 'queueschell' para ver o processamento dos processos\n");
        pthread_t newThread;

        pthread_create(&newThread, NULL, escalonadorFIFOandLRU, NULL);
    }else if(strcmp(politicaG, "MFP") == 0){
        printf("Iniciando escalonamento dos processos em modo %s\n", politicaG);
        printf("Utilize o comando 'queueschell' para ver o processamento dos processos\n");
        pthread_t newThread;

        pthread_create(&newThread, NULL, escalonadorMFP, NULL);
    }else{
        printf("\nNão foi possível escalonar. Tenha certeza que digitou corretamente a política a ser aplicada!!\n");
    }

}

void manipulaProcesso(){
    auxQtdCiclo = qtdCiclos; 
    insereNoProcessador(pG, pAuxG);
    if(qtdCiclos > 1){
        strcpy(pAuxG->init_type,types[rand() % 3]); //Após o primeiro ciclo, utiliza o randômico para definir o typo do processo: cpu, memory ou io bound.
    }
    /* system("clear"); //remover
    listaDeProcessos(filaDeProcessos); //remover */
    if(strcmp(pAuxG->init_type, "cpu-bound") == 0 && pAuxG->ciclos > 0){
        strcpy(pAuxG->status,"executando");
        /* system("clear"); //remover
        listaDeProcessos(filaDeProcessos); //remover */
        double quantum = 1 + rand() % ((int)pAuxG->max_quantum);
        sleep(quantum);
        double cicloRealizado = (quantum/pAuxG->max_quantum) > pAuxG->ciclos ? pAuxG->ciclos : (quantum/pAuxG->max_quantum);
        pAuxG->ciclos = pAuxG->ciclos - cicloRealizado;
        pAuxG->timestamp = pAuxG->timestamp + quantum;
        /* system("clear"); //remover
        listaDeProcessos(filaDeProcessos); //remover */
        if(pAuxG->ciclos <= 0.09){
            pAuxG->ciclos = 0;
            strcpy(pAuxG->status,"finalizado");
            auxDoneProcess++;
            /* system("clear"); //remover
            listaDeProcessos(filaDeProcessos); //remover */
        }else{
            strcpy(pAuxG->status,"pronto");
        }
        removeDoProcessador(pG, pG->primeiro);
        if(resultados != NULL)
            fprintf(resultados,"\t%s %d%s %0.f%s %d%s %.2f%s %s\n","ID:", pAuxG->id, "; QUANTUM:", quantum, "; TIMESTAMP:", pAuxG->timestamp, "; CICLO(S)_REALIZADO(S):", cicloRealizado, "; TYPE:", pAuxG->init_type);
    }else if(pAuxG->ciclos > 0){
        removeDoProcessador(pG, pG->primeiro);
        if(strcmp(pAuxG->init_type, "io-bound") == 0){
            strcpy(pAuxG->status,"bloqueado");
            /* system("clear"); //remover
            listaDeProcessos(filaDeProcessos); //remover */
            int sleepAux = 1 + (rand() % 4); 
            sleep(sleepAux);//punição do processo
            pAuxG->timestamp = pAuxG->timestamp + sleepAux;
            empilharNoDisco(dG, pAuxG);
            strcpy(pAuxG->status,"executando");
            double quantum = 1 + rand() % ((int)pAuxG->max_quantum);
            sleep(quantum);
            double cicloRealizado = (quantum/pAuxG->max_quantum) > pAuxG->ciclos ? pAuxG->ciclos : (quantum/pAuxG->max_quantum);
            pAuxG->ciclos = pAuxG->ciclos - cicloRealizado;
            pAuxG->timestamp = pAuxG->timestamp + quantum;
            /* system("clear"); //remover
            listaDeProcessos(filaDeProcessos); //remover */
            if(pAuxG->ciclos <= 0.09){
                pAuxG->ciclos = 0;
                strcpy(pAuxG->status,"finalizado");
                auxDoneProcess++;
                /* system("clear"); //remover
                listaDeProcessos(filaDeProcessos); //remover */
            }else{
                strcpy(pAuxG->status,"pronto");
            }
            if(resultados != NULL)
                fprintf(resultados,"\t%s %d%s %0.f%s %d%s %.2f%s %s\n","ID:", pAuxG->id, "; QUANTUM:", quantum, "; TIMESTAMP:", pAuxG->timestamp, "; CICLO(S)_REALIZADO(S):", cicloRealizado, "; TYPE:", pAuxG->init_type);
        }else if(strcmp(pAuxG->init_type, "memory-bound") == 0){
            strcpy(pAuxG->status,"bloqueado");
            /* system("clear"); //remover
            listaDeProcessos(filaDeProcessos); //remover */
            int sleepAux = 1 + (rand() % 4); 
            sleep(sleepAux);//punição do processo
            pAuxG->timestamp = pAuxG->timestamp + sleepAux;
            insereNaMemoria(mG, pAuxG);
            strcpy(pAuxG->status,"executando");
            double quantum = 1 + rand() % ((int)pAuxG->max_quantum);
            sleep(quantum);
            double cicloRealizado = (quantum/pAuxG->max_quantum) > pAuxG->ciclos ? pAuxG->ciclos : (quantum/pAuxG->max_quantum);
            pAuxG->ciclos = pAuxG->ciclos - cicloRealizado;
            pAuxG->timestamp = pAuxG->timestamp + quantum;
            /* system("clear"); //remover
            listaDeProcessos(filaDeProcessos); //remover */
            if(pAuxG->ciclos <= 0.09){
                pAuxG->ciclos = 0;
                strcpy(pAuxG->status,"finalizado");
                auxDoneProcess++;
                /* system("clear"); //remover
                listaDeProcessos(filaDeProcessos); //remover */
            }else{
                strcpy(pAuxG->status,"pronto");
            }
            if(resultados != NULL)
                fprintf(resultados,"\t%s %d%s %0.f%s %d%s %.2f%s %s\n","ID:", pAuxG->id, "; QUANTUM:", quantum, "; TIMESTAMP:", pAuxG->timestamp, "; CICLO(S)_REALIZADO(S):", cicloRealizado, "; TYPE:", pAuxG->init_type);
        }
    }
}

void* escalonadorFIFOandLRU(){
    //A diefrença do FIFO pro LRU é que o LRU ordena a lista toda vez que termina um ciclo

    resultados = fopen("resultados.txt", "w");
    if(resultados == NULL) {
        printf("Não foi possível criar o arquivo para escrever os resultados!!\n");
    }

    time_t inicio, fim;
    time(&inicio);
    
    BlocoLista *b = filaDeProcessosG->primeiro;
    if(filaDeProcessosG->primeiro == filaDeProcessosG->ultimo){
        printf("Não existem processos na fila\n");
        return NULL;
    }

    while((filaDeProcessosG->cont - auxDoneProcess) != 0){
        b = b->proximo;
        pAuxG = b == NULL ? NULL : b->processo;
        if(qtdCiclos != auxQtdCiclo){
            if(strcmp(politicaG, "LRU") == 0)
                sortProcess(filaDeProcessosG);
            fprintf(resultados,"%s %d \n","PROCESSOS QUE RODARAM NO CICLO ", qtdCiclos);
        }

        if(pAuxG != NULL){
            manipulaProcesso();
        }else{
            /* printf("Fim do ciclo %d; Processos totais %d; Processos finalizados %d\n", qtdCiclos, filaDeProcessos->cont, auxDoneProcess);
            listaDeProcessos(filaDeProcessos); */
            b = filaDeProcessosG->primeiro;
            qtdCiclos++;
            fprintf(resultados,"\n\n");
        }
    }
    time(&fim);
    time_t tempoTotal = fim - inicio;
    printf("Todos os processos foram executados\n");
    fprintf(resultados,"\n\n%s %ld\n","Tempo total corrido para o processamento do lote: ", tempoTotal);
    fclose(resultados);
    return NULL;
}

void *escalonadorMFP(){ //MFP = Múltiplas Filas de Prioridade

    resultados = fopen("resultados.txt", "w");
    if(resultados == NULL) {
        printf("Não foi possível criar o arquivo para escrever os resultados!!\n");
    }

    time_t inicio, fim;
    time(&inicio);
    
    Processador *filaPrioridade4 = (Processador*)malloc(sizeof(Processador));
    iniciaProcessador(filaPrioridade4);
    separaProcessosPrioridade(filaPrioridade4, 4);
    
    Processador *filaPrioridade3 = (Processador*)malloc(sizeof(Processador));
    iniciaProcessador(filaPrioridade3);
    separaProcessosPrioridade(filaPrioridade3, 3);
    
    Processador *filaPrioridade2 = (Processador*)malloc(sizeof(Processador));
    iniciaProcessador(filaPrioridade2);
    separaProcessosPrioridade(filaPrioridade2, 2);
    
    Processador *filaPrioridade1 = (Processador*)malloc(sizeof(Processador));
    iniciaProcessador(filaPrioridade1);
    separaProcessosPrioridade(filaPrioridade1, 1);

    while(filaPrioridade4->cont != 0){
        manipulaProcessoMFP(filaPrioridade4, filaPrioridade3);
    }

    while(filaPrioridade3->cont != 0){
        manipulaProcessoMFP(filaPrioridade3, filaPrioridade2);
    }

    while(filaPrioridade2->cont != 0){
        manipulaProcessoMFP(filaPrioridade2, filaPrioridade1);
    }

    sleep(2);
    printf("Passou dos manipulas\n");

    BlocoLista *b = filaDeProcessosG->primeiro;
    if(filaDeProcessosG->primeiro == filaDeProcessosG->ultimo){
        printf("Não existem processos na fila\n");
        return NULL;
    }

    fprintf(resultados,"\n\n");
    fprintf(resultados,"%s\n","INÍCIO DO PROCESSO DE LOTERIA");

    while((filaDeProcessosG->cont - auxDoneProcess) != 0){
        
        sortProcessBilhetes(filaDeProcessosG);
        b = filaDeProcessosG->primeiro;
        b = b->proximo;
        pAuxG = b == NULL ? NULL : b->processo;
        sorteiaBilhetes(pAuxG->id);

        if(pAuxG != NULL){
            manipulaProcesso();
        }
    }

    time(&fim);
    time_t tempoTotal = fim - inicio;
    printf("Todos os processos foram executados\n");
    fprintf(resultados,"\n\n%s %ld\n","Tempo total corrido para o processamento do lote: ", tempoTotal);
    fclose(resultados);
    return NULL;
}

void sorteiaBilhetes(int idExecutado){
    int n = filaDeProcessosG->tam;
    BlocoLista *b = filaDeProcessosG->primeiro;
    for(int i = 0; i < n; i++){
        if(b->proximo){
            b = b->proximo;
            if(b->processo->id != idExecutado && strcmp(b->processo->status, "finalizado") != 0){
                b->processo->bilhetes++;
            }else if(b->processo->id == idExecutado || strcmp(b->processo->status, "finalizado") == 0){
                b->processo->bilhetes = 0;
            }
        }
    }
}

void separaProcessosPrioridade(Processador *l, int prioridade){
    int n = filaDeProcessosG->tam;
    BlocoLista *b = filaDeProcessosG->primeiro;
    for(int i = 0; i < n; i++){
        if(b->proximo){
            b = b->proximo;
            if(b->processo->prioridade == prioridade){
                l->tam++;
                insereNoProcessador(l, b->processo);
            }
        }
    }
}

void manipulaProcessoMFP(Processador *atual, Processador *futura){
    BlocoLista *b = atual->primeiro;
    if(atual->primeiro == atual->ultimo){
        return;
    }

    int prioridade = b->proximo->processo->prioridade;

    while(atual->cont != 0){
        b = b->proximo;
        pAuxG = b == NULL ? NULL : b->processo;

        if(qtdCiclos != auxQtdCiclo){
            fprintf(resultados,"%s %d %s %d \n","PROCESSOS QUE RODARAM NO CICLO ", qtdCiclos, " E PRIORIDADE ", prioridade);
        }

        if(pAuxG != NULL){
            if(prioridade == pAuxG->prioridade){
                if((pAuxG->ciclosTotais - pAuxG->ciclos) < 1){
                    manipulaProcesso();
                }else{
                    pAuxG->prioridade--;
                    atual->cont--;
                    futura->tam++;
                    insereNoProcessador(futura, pAuxG);
                }
            }
            auxQtdCiclo = qtdCiclos;
        }else{
            b = atual->primeiro;
            qtdCiclos++;
            fprintf(resultados,"\n\n");
        }
    }
}

void sortProcess(Processador *l) { //Utiliza o shell sort para ordenar, n = Tamanho da lista, l = Lista de processos
    int n = l->tam;
    Processo *p = (Processo*)malloc(n*sizeof(Processo));
    BlocoLista *b = l->primeiro;
    for(int i = 0; i < n; i++){
        if(b->proximo){
            b = b->proximo;
            p[i] = *(b->processo);
        }
    }

    //Aqui começa o ShellSort
    int h = 1;
    Processo aux; 
    int j;

    do{
        h = 3 * h + 1;
    }while(h<n);

    while(h > 0){
        h = h/3;
        for(int i=h; i<n; i++){
            j=i;
            aux = p[i];
            while(j > h-1 && p[j-h].ciclos > aux.ciclos){
                p[j] = p[j-h];
                j = j - h;
            }
            p[j] = aux;
        }
    }
    //Aqui termina o ShellSort
    
    b = l->primeiro;
    for(int i = 0; i < n; i++){
        if(b->proximo){
            b = b->proximo;
            *(b->processo) = p[i];
        }
    }
}

void sortProcessBilhetes(Processador *l) { //Utiliza o shell sort para ordenar, n = Tamanho da lista, l = Lista de processos
    int n = l->tam;
    Processo *p = (Processo*)malloc(n*sizeof(Processo));
    BlocoLista *b = l->primeiro;
    for(int i = 0; i < n; i++){
        if(b->proximo){
            b = b->proximo;
            p[i] = *(b->processo);
        }
    }

    //Aqui começa o ShellSort
    int h = 1;
    Processo aux; 
    int j;

    do{
        h = 3 * h + 1;
    }while(h<n);

    while(h > 0){
        h = h/3;
        for(int i=h; i<n; i++){
            j=i;
            aux = p[i];
            while(j > h-1 && p[j-h].bilhetes < aux.bilhetes){
                p[j] = p[j-h];
                j = j - h;
            }
            p[j] = aux;
        }
    }
    //Aqui termina o ShellSort
    
    b = l->primeiro;
    for(int i = 0; i < n; i++){
        if(b->proximo){
            b = b->proximo;
            *(b->processo) = p[i];
        }
    }
}

/* void *testThread(){
    char opcao[100];
    printf("Me conta seu nome aí mano");
    fgets(opcao, 100, stdin);
    printf("Maneiro, então seu nome é %s", opcao);
    return NULL;
} */