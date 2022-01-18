#include "Processador.h"
#include "Disco.h"
#include "Memoria.h"
#include "JsonReader.h"

int main(){
    char opcoes[15];

    Memoria *memoria = (Memoria*)malloc(sizeof (Memoria));
    Processador *cpu = (Processador*)malloc(sizeof (Processador));
    Processador *filaDeProcessos = (Processador*)malloc(sizeof (Processador));
    Disco *disco = (Disco*)malloc(sizeof (Disco));
    char* politica = (char*)malloc(sizeof (char));
    
    iniciaEstruturas(politica, memoria, cpu, disco);
    system("clear");
    printf("    help:\tLista os comandos disponíveis no shell\n");
    printf("    meminfo:\tExibe as informações da memória RAM\n");
    printf("    queueschell:\tDetalha quais processos estão sendo gerenciados.\n");
    printf("    cpuinfo:\tDetalha qual processo está em execução\n");
    printf("    execute:\tExecuta a fila de processos\n");
    printf("    kill -9:\tFinaliza a execução do sistema operacional\n");
    printf("    load:\tCarrega a lista de processos\n");
    printf("    clear:\tLimpa o shell\n");
    printf("    exit:\tFinaliza a execução do programa\n");
    printf("\n\n");
    while(TRUE){
        //printf(">>>");
        fgets(opcoes, 15, stdin);
        if(strcmp(opcoes, "help\n") == 0){
            printf("    help:\tLista os comandos disponíveis no shell\n");
            printf("    meminfo:\tExibe as informações da memória RAM\n");
            printf("    queueschell:\tDetalha quais processos estão sendo gerenciados.\n");
            printf("    cpuinfo:\tDetalha qual processo está em execução\n");
            printf("    execute:\tExecuta a fila de processos\n");
            printf("    kill -9:\tFinaliza a execução do sistema operacional\n");
            printf("    load:\tCarrega a lista de processos\n");
            printf("    clear:\tLimpa o shell\n");
            printf("    exit:\tFinaliza a execução do programa\n");
            printf("\n\n");
        }else if(strcmp(opcoes, "meminfo\n") == 0){
            memInfo(memoria);
            printf("\n\n");
        }else if(strcmp(opcoes, "queueschell\n") == 0 ){
            listaDeProcessos(filaDeProcessos);
            printf("\n\n");
        }else if(strcmp(opcoes, "cpuinfo\n") == 0 ){
            cpuInfo(cpu);
            printf("\n\n");
        }else if(strcmp(opcoes, "execute\n") == 0 ){
            printf("    Não existem processos para serem executados!!\n");
            printf("\n\n");
        }else if(strcmp(opcoes, "kill -9\n") == 0 ){
            printf("    Não é possível 'matar' um processo, pois a fila está vazia!!\n");
            printf("\n\n");
        }else if(strcmp(opcoes, "load\n") == 0 ){
            readJsonProcessos("processos.json", filaDeProcessos, politica, memoria, cpu, disco);
            printf("\n\n");
        }else if(strcmp(opcoes, "clear\n") == 0 ){
            system("clear");
        }else if(strcmp(opcoes, "exit\n") == 0 ){
            return 0;
        }else{
            printf("    Comando inválido. Use 'help' para saber quais são os comandos disponíveis\n");
        }
    }

    return 0;
}