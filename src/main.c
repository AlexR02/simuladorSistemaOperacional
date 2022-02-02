#include "Processador.h"
#include "Disco.h"
#include "Memoria.h"
#include "JsonReader.h"

int threadEx = 0;
int loop = 0;
Memoria *memoria;
Processador *cpu;
Processador *filaDeProcessos;
Disco *disco;

void help(){
    printf("    help:\t\tLista os comandos disponíveis no shell\n");
    printf("    meminfo:\t\tExibe as informações da memória RAM\n");
    printf("    queueschell:\tDetalha quais processos estão sendo gerenciados.\n");
    printf("    cpuinfo:\t\tDetalha qual processo está em execução no processador\n");
    printf("    execute:\t\tExecuta a fila de processos\n");
    printf("    kill -9:\t\tFinaliza a execução do sistema operacional\n");
    printf("    load:\t\tCarrega a lista de processos\n");
    printf("    clear:\t\tLimpa o shell\n");
    printf("    exit:\t\tFinaliza a execução do programa\n");
    printf("\n\n");
}

void* queueschell(){
    loop = 0;
    while(loop == 0){
        listaDeProcessos(filaDeProcessos);
        sleep(1);
        system("clear");
    }
    loop = 0;
    return NULL;
}

void* cpuInfoMain(){
    loop = 0;
    while(loop == 0){
        cpuInfo(cpu);
        sleep(1);
        system("clear");
    }
    loop = 0;
    return NULL;
}

void* memInfoMain(){
    loop = 0;
    while(loop == 0){
        memInfo(memoria);
        sleep(1);
        system("clear");
    }
    loop = 0;
    return NULL;
}

int main(){
    char opcoes[15];

    memoria = (Memoria*)malloc(sizeof (Memoria));
    cpu = (Processador*)malloc(sizeof (Processador));
    filaDeProcessos = (Processador*)malloc(sizeof (Processador));
    disco = (Disco*)malloc(sizeof (Disco));
    char* politica = (char*)malloc(sizeof (char));
    
    iniciaEstruturas(politica, memoria, cpu, disco);
    system("clear");
    help();

    while(TRUE){
        if(loop == 1){
            system("clear");
            help();
        }
        printf(">>>");
        fgets(opcoes, 15, stdin);
        if(strcmp(opcoes, "help\n") == 0){
            help();
        }else if(strcmp(opcoes, "meminfo\n") == 0){
            system("clear");
            pthread_t newThread;
            pthread_create(&newThread, NULL, memInfoMain, NULL);
            char stop;
            scanf("%c", &stop);
            loop = 1;
            pthread_join(newThread, NULL);
            system("clear");
            help();
        }else if(strcmp(opcoes, "queueschell\n") == 0 ){
            system("clear");
            pthread_t newThread;
            pthread_create(&newThread, NULL, queueschell, NULL);
            char stop;
            scanf("%c", &stop);
            loop = 1;
            pthread_join(newThread, NULL);
            system("clear");
            help();
        }else if(strcmp(opcoes, "cpuinfo\n") == 0 ){
            system("clear");
            pthread_t newThread;
            pthread_create(&newThread, NULL, cpuInfoMain, NULL);
            char stop;
            scanf("%c", &stop);
            loop = 1;
            pthread_join(newThread, NULL);
            system("clear");
            help();
        }else if(strcmp(opcoes, "execute\n") == 0 ){
            executeProcessos();
            printf("\n\n");
        }else if(strcmp(opcoes, "kill -9\n") == 0 ){
            printf("Ainda não implementado, utilize 'exit' para sair e então utilize 'make run' novamente!!\n");
            printf("\n\n");
        }else if(strcmp(opcoes, "load\n") == 0 ){
            readJsonProcessos("processos.json", filaDeProcessos);
            printf("\n\n");
        }else if(strcmp(opcoes, "clear\n") == 0 ){
            system("clear");
        }else if(strcmp(opcoes, "exit\n") == 0 ){
            return 0;
        }else if(strcmp(opcoes, "sort\n") == 0 ){
            sortProcess(filaDeProcessos);
            listaDeProcessos(filaDeProcessos);
            printf("\n\n");
        }else if(strcmp(opcoes, "MFP\n") == 0 ){
            escalonadorMFP();
            printf("\n\n");
        }else{
            printf("    Comando inválido. Use 'help' para saber quais são os comandos disponíveis\n");
        }
    }

    return 0;
}