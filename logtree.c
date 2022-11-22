#include <stdlib.h>
#include "./logtree.h"

Log **log_inicializar(Log **l) {
    /**Descrição: Inicializa um registrador
     * Autor: Diego
     * 
     * Args: l : Log **
     * 
     * Returns: None
     * 
    */
    l = (Log **) malloc(sizeof(Log *));
    (*l) = NULL;
    return l;
}

void log_registrar(Log **l, int conta, int classe, int timer, int caixa) {
    /**Descrição: Registra um cliente no registrador
     * Autor: Diego
     * 
     * Args: [
     *      l : Log **,
     *      conta : int,
     *      classe : int,
     *      timer : int,
     *      caixa : int
     * ]
     * 
     * Returns: None
     * 
    */
    Log *temp = (Log *)malloc(sizeof(Log));
    temp->conta = conta;
    temp->classe = classe;
    temp->timer = timer;
    temp->caixa = caixa;

    Log *y = NULL;
    Log *x = (*l);

    while (x != NULL) {
        y = x;
        x = (temp->timer < x->timer) ? x->esq : x->dir;
    }

    if (y == NULL) {
        (*l) = temp;
    } else if (temp->timer < y->timer) {
        y->esq = temp;
    } else {
        y->dir = temp;
    }
}

float log_media_por_classe(Log *l, int classe) {
    /**Descrição: Calcula a média de tempo de uma classe
     * Autor: Diego
     * 
     * Args: [
     *      l : Log *,
     *      classe : int
     * ]
     * 
     * Returns: media : float
     * 
    */
    int total = 0;
    int count = 0;
    float media;
    
    if (l != NULL) {
        log_media_por_classe(l->esq, classe);
        if (l->classe == classe) {
            total += l->timer;
            count++;
        }
        log_media_por_classe(l->dir, classe);
    }

    media = ((float) total)/((float) count);
    return media;
}
