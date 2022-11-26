#include "escalonador.h"
#include "fila_fifo.h"
#include <stdlib.h>

void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5){
    e->caixas = caixas;
    e->delta_t = delta_t;
    e->n_1 = n_1;
    e->n_2 = n_2;
    e->n_3 = n_3;
    e->n_4 = n_4;
    e->n_5 = n_5;
    f_inicializar(&e->fila_1);
    f_inicializar(&e->fila_2);
    f_inicializar(&e->fila_3);
    f_inicializar(&e->fila_4);
    f_inicializar(&e->fila_5);
};

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes) {
    
}