#include "Processo.h"

void imprimeProcesso(Processo p){
    printf("%d\t%d\t%d\t\t%s\t\t%d\t\t%d\t%s\n",p.id, p.ciclos, p.max_quantum, p.init_type, p.timestamp, p.prioridade, p.status);
}