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
    (*l) = NULL;
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

float log_media_por_classe(Log **l, int classe) {
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
    Log *atual, *pre;
    int total = 0, cont = 0;
    float media;
    
    atual = ((*l) == NULL) ? (NULL) : ((*l));
    
    while (atual != NULL) {
        if (atual->esq == NULL) {
            cont++;
            total += atual->timer;
            atual = atual->esq;
        } else {
            pre = atual->esq;
            while ((pre->dir != NULL) && (pre->dir != atual))
                pre = pre->dir;
            if (pre->dir == NULL) {
                pre->dir = atual;
                atual = atual->esq;
            } else {
                pre->dir = NULL;
                cont++;
                total += atual->timer;
                atual = atual->dir;
            }
        }
    }
    
    media = ((float) total)/((float) cont);
    return media;
}

int log_obter_soma_por_classe(Log **l, int classe) {
    /**Descrição: Retorna a soma do tempo de espera de uma classe
     * Autor: Diego
     * 
     * Args : [
     *      l : Log **,
     *      classe : int     
     * ]
     * 
     * Returns: soma : int
     * 
    */
}