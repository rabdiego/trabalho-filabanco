#include <stdlib.h>
#include "./logtree.h"

void log_inicializar(Log **l) {
    /**Descrição: Inicializa um registrador
     * Autor: Diego
     * 
     * Args: l : Log **
     * 
     * Returns: None
     * 
    */
    l = (Log **) malloc(sizeof(Log *));
    *l = NULL;
}

void log_registrar(Log **l, int conta, int chave, int timer, int caixa) {
    /**Descrição: Registra um cliente no registrador
     * Autor: Diego
     * 
     * Args: [
     *      l : Log **,
     *      conta : int,
     *      chave : int,
     *      timer : int,
     *      caixa : int
     * ]
     * 
     * Returns: None
     * 
    */
    Log _z = {conta, chave, timer, caixa, NULL, NULL, NULL};
    Log *z = &_z;
    Log *y = NULL;
    Log *x = *l;

    while (x != NULL) {
        y = x;
        x = (z->timer < x->timer) ? x->esq : x->dir;
    }

    z->pai = y;
    if (y == NULL) {
        *l = z;
    } else if (z->timer < y->timer) {
        y->esq = z;
    } else {
        y->dir = z;
    }
}