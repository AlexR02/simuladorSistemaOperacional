#include "Processador.h"

void iniciaProcessador(Processador *lista){
    lista->primeiro = (BlocoLista*)malloc(sizeof(BlocoLista));
    lista->ultimo = lista->primeiro;
    lista->primeiro->proximo = NULL;
    lista->cont = 0;
}
void insereNoProcessador(Processador *lista, Processo *processo){
    if(lista->tam > 0 && lista->tam > lista->cont){
        lista->ultimo->proximo = (BlocoLista*)malloc(sizeof(BlocoLista));
        lista->ultimo = lista->ultimo->proximo;
        lista->ultimo->processo = processo;
        lista->ultimo->proximo = NULL;
        if(processo != NULL)
            lista->cont++;
    }
}

void removeDoProcessador(Processador *lista, BlocoLista *b){
    BlocoLista *aux;

    if(lista->primeiro == lista->ultimo || b >= lista->ultimo){
        printf("Não existem processos nesse processador ou posição não existe\n");
        return;
    }
    
    aux = b->proximo;
    b->proximo = aux->proximo;

    if(b->proximo == NULL){
        lista->ultimo = b;
        lista->cont--;
    }
}

void cpuInfo(Processador *lista){
    BlocoLista *b = lista->primeiro;
    if(lista->primeiro == lista->ultimo){
        printf("Esse processador está sem processos\n");
        return;
    }
    int aux = 0;
    while(b->proximo){
        b = b->proximo;
        if(b->processo == NULL){
            printf("Não existem processos sendo executados no processoador\n");
        }else{
            if(aux > 0){
                imprimeProcesso(*b->processo);
            }else{
                printf("id\tciclos\tmax_quantum\tinit_type\ttimestamp\tpropriedade\n");
                imprimeProcesso(*b->processo);
            }
            ++aux;
        }
    }
}

void listaDeProcessos(Processador *lista){
    BlocoLista *b = lista->primeiro;
    if(lista->primeiro == lista->ultimo){
        printf("Não existem processos na fila\n");
        return;
    }
    int aux = 0;
    while(b->proximo){
        b = b->proximo;
        if(b->processo == NULL){
            printf("Não existem processos na fila\n");
        }else{
            if(aux > 0){
                imprimeProcesso(*b->processo);
            }else{
                printf("id\tciclos\tmax_quantum\tinit_type\ttimestamp\tprioridade\tstatus\n");
                imprimeProcesso(*b->processo);
            }
            ++aux;
        }
    }
}