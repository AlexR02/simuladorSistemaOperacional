#include "Processador.h"

void iniciaProcessador(Processador *lista){
    lista->primeiro = (BlocoLista*)malloc(sizeof(BlocoLista));
    lista->ultimo = lista->primeiro;
    lista->primeiro->proximo = NULL;
    lista->cont = 0;
}
void insereNoProcessador(Processador *lista, Processo processo){
    lista->ultimo->proximo = (BlocoLista*)malloc(sizeof(BlocoLista));
    lista->ultimo = lista->ultimo->proximo;
    lista->ultimo->processo = processo;
    lista->ultimo->proximo = NULL;
    lista->cont++;
}

void removeDoProcessador(Processador *lista, BlocoLista *b, Processo *processo){
    BlocoLista *aux;

    if(lista->primeiro == lista->ultimo || b >= lista->ultimo){
        printf("Não existem processos nesse processador ou posição não existe\n");
        return;
    }
    
    aux = b->proximo;
    *processo = aux->processo;
    b->proximo = aux->proximo;

    if(b->proximo == NULL){
        lista->ultimo = b;
        lista->cont--;
        free(aux);
    }
}

/* void imprimeProcessador(Processador *lista){
    BlocoLista *b = lista->primeiro;
    if(lista->primeiro == lista->ultimo){
        printf("Essa lista está vazia ou dado não existe\n");
        return;
    }
    while(b->proximo){
        b = b->proximo;
        printf("UserID: %d\tMovieID: %d\tRating: %d\n", b->item.userID, b->item.movieID, b->item.rating);
    }
    printf("O tamanho da lista: %d\n", lista->cont);
} */