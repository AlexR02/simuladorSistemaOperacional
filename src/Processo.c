#include "Processo.h"

void imprimeProcesso(Processo p){
    printf("%d\t%.2f\t%0.f\t\t%s\t\t%d\t\t%d\t%s\t\t%d\n",p.id, p.ciclos, p.max_quantum, p.init_type, p.timestamp, p.prioridade, p.status, p.bilhetes);
}