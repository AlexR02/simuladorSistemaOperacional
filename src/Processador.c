#include "Processador.h"

void iniciaProcessador(Processador *lista){
    lista->primeiro = (BlocoLista*)malloc(sizeof(BlocoLista));
    lista->ultimo = lista->primeiro;
    lista->primeiro->proximo = NULL;
    lista->cont = 0;
}
void insereNoProcessador(Processador *lista, Processo *processo){
    lista->ultimo->proximo = (BlocoLista*)malloc(sizeof(BlocoLista));
    lista->ultimo = lista->ultimo->proximo;
    lista->ultimo->processo = processo;
    lista->ultimo->proximo = NULL;
    lista->cont++;
}

/* void removeDoProcessador(Processador *lista, BlocoLista *b, Processo *processo){
    BlocoLista *aux;

    if(lista->primeiro == lista->ultimo || b >= lista->ultimo){
        printf("Não existem processos nesse processador ou posição não existe\n");
        return;
    }
    
    aux = b->proximo;
    processo = aux->processo;
    b->proximo = aux->proximo;

    if(b->proximo == NULL){
        lista->ultimo = b;
        lista->cont--;
        free(aux);
    }
} */

void cpuInfo(Processador *lista){
    BlocoLista *b = lista->primeiro;
    if(lista->primeiro == lista->ultimo){
        printf("Esse processador está sem processos\n");
        return;
    }
    while(b->proximo){
        b = b->proximo;
        if(b->processo == NULL){
            printf("Não existem processos sendo executados no processoador\n");
        }else{
            printf("Descrição: %s\n", b->processo->descricao);
            printf("Identificação: %d\n", b->processo->id);
            printf("TimeStamp: %d\n", b->processo->timestamp);
            printf("Quantum: %d\n", b->processo->quantum);
        }
    }
}