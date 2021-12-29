#include "Disco.h"

void iniciaDisco(Disco *disco){
    disco->top = (Bloco_pilha*)malloc(sizeof(Bloco_pilha));
    disco->top->proximo = NULL;
    disco->tam = 0;
}

void empilharNoDisco(Disco *disco, Processo *processo){
    Bloco_pilha *aux;
    aux = (Bloco_pilha*)malloc(sizeof(Bloco_pilha));
    disco->top->processo = processo;
    aux->proximo = disco->top;
    disco->top = aux;
    disco->tam++;
}

/* void desempilhar(Disco *disco, Processo *processo){
    Bloco_pilha *q;
    if(!disco->top->proximo){
        printf("O disco está vazio!!\n");
        return;
    }
    q = disco->top;
    disco->top = q->proximo;
    processo = q->proximo->processo;
    free(q);
    disco->tam--;
} */

void desempilharTodos(Disco *disco){
    Bloco_pilha *q;
    if(!disco->top->proximo){
        printf("O disco está vazio!!\n");
        return;
    }
    while(disco->tam != 0){
        q = disco->top;
        disco->top = q->proximo;
        free(q);
        disco->tam--;
    }
}

int tamanho(Disco pilha){
    return(pilha.tam);
}

int buscarProcesso(Disco *disco, int id){
    Bloco_pilha *q = disco->top;
    int cont = 0;
    if(!q->proximo){
        return cont;
    }
    cont++;
    while(q->proximo){
        q = q->proximo;
        if(id == q->processo->id){
            cont++;
            return cont;
        }
    }
    return cont;
}

/* void imprimeDisco(Disco *disco){
    Bloco_pilha *q = disco->top;
    if(!q->proximo){
        printf("A pilha está vazia!!\n");
        return;
    }
    while(q->proximo){
        q = q->proximo;
        printf("UserID: %d\tValor: %d\n", q->user.userID, q->user.k);
    }
    printf("O tam da pilha: %d\n", disco->tam);
} */