#include "escalonador.h"
#include "fila_fifo.h"
#include <stdlib.h>

void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5){
    /**Descrição: Inicializa o escalonador
     * Autor: Diego
     * 
     * Args: [
     *      e : Escalonador *,
     *      caixas : int,
     *      delta_t : int,
     *      n_1 : int,
     *      n_2 : int,
     *      n_3 : int,
     *      n_4 : int,
     *      n_5 : int
     * ]
     * 
     * Returns: None
     * 
    */
    
    e->caixas = caixas;
    e->delta_t = delta_t;
    e->n_1 = n_1;
    e->n_2 = n_2;
    e->n_3 = n_3;
    e->n_4 = n_4;
    e->n_5 = n_5;
    f_inicializar(&(e->fila_1));
    f_inicializar(&(e->fila_2));
    f_inicializar(&(e->fila_3));
    f_inicializar(&(e->fila_4));
    f_inicializar(&(e->fila_5));
};

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes) {
    /**Descrição: Insere um cliente no escalonador
     * Autor: Diego
     * 
     * Args : [
     *      e : Escalonador *,
     *      classe : int,
     *      num_conta : int,
     *      qtde_operacoes : int
     * ]
     * 
     * Returns : int
    */
    
    switch (classe) {
        case 5:
            f_inserir(&(e->fila_5), num_conta, qtde_operacoes);
            break;
        case 4:
            f_inserir(&(e->fila_5), num_conta, qtde_operacoes);
            break;
        case 3:
            f_inserir(&(e->fila_5), num_conta, qtde_operacoes);
            break;
        case 2:
            f_inserir(&(e->fila_5), num_conta, qtde_operacoes);
            break;
        case 1:
            f_inserir(&(e->fila_5), num_conta, qtde_operacoes);
            break;
        default:
            return 0;
            break;
    }
    return 1;
}