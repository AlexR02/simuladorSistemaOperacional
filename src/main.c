#include "Processador.h"
#include "Disco.h"
#include "Memoria.h"
#include "JsonReader.h"

int main(){
    char opcoes[15];

    Memoria *memoria = (Memoria*)malloc(sizeof (Memoria));;
    Processador *cpu = (Processador*)malloc(sizeof (Processador));;
    Disco *disco = (Disco*)malloc(sizeof (Disco));;
    
    iniciaEstruturas(memoria, cpu, disco);

    while(TRUE){
        printf("Insira a opção>>>");
        fgets(opcoes, 15, stdin);
        if(strcmp(opcoes, "help\n") == 0){
            printf("    meminfo: exibe os dados ");
            printf("    queueschell: detalha qual proocesso está em execução \n");
            printf("    cpuinfo: detalha qual processo está em execução \n");
            printf("    execute: Executa a fila de processos \n");
            printf("    kill -9: Finaliza a execução do sistema operacional \n");
            printf("    clear: Limpa o shell \n");
            printf("    ^c: Finaliza a execução do programa\n");
        }else if(strcmp(opcoes, "meminfo\n") == 0){
            memInfo(memoria);
        }else if(strcmp(opcoes, "queueschell\n") == 0 ){
            printf("    Não existem processos sendo executados no momento!!\n");
        }else if(strcmp(opcoes, "cpuinfo\n") == 0 ){
            cpuInfo(cpu);
        }else if(strcmp(opcoes, "execute\n") == 0 ){
            printf("    Não existem processos para serem executados!!\n");
        }else if(strcmp(opcoes, "kill -9\n") == 0 ){
            printf("    Não é possível 'matar' um processo, pois a fila está vazia!!\n");
        }else if(strcmp(opcoes, "clear\n") == 0 ){
            system("clear");
        }else{
            printf("    Opção inválida. Use 'help' para saber quais são as opções disponíveis\n");
        }
    }

    return 0;
}