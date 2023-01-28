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

    // Algoritmo de inclusão na ABB
    Log *y = NULL;
    Log *x = (*l);

    // Percorrendo a árvore até o local correto
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

// Próximas duas funções usam o algoritmo EM ORDEM da ABB

int log_obter_soma_por_classe(Log **l, int classe) {
    /**Descrição: Retorna a soma do tempo de espera total de uma classe
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
    Log *esq, *dir;
    int soma = 0;

    esq = ((*l) == NULL) ? (NULL) : ((*l)->esq);
    dir = ((*l) == NULL) ? (NULL) : ((*l)->dir);

    if ((*l) != NULL) {
        soma += log_obter_soma_por_classe(&esq, classe);
        if ((*l)->classe == classe)
            soma += (*l)->timer;
        soma += log_obter_soma_por_classe(&dir, classe);
    }

    return soma;
}

int log_obter_contagem_por_classe(Log **l, int classe) {
    /**Descrição: Retorna o total de clientes de uma classe
     * Autor: Diego
     * 
     * Args : [
     *      l : Log **,
     *      classe : int
     * ]
     * 
     * Returns: cont : int
     * 
    */
    Log *esq, *dir;
    int cont = 0;

    esq = ((*l) == NULL) ? (NULL) : ((*l)->esq);
    dir = ((*l) == NULL) ? (NULL) : ((*l)->dir);

    if ((*l) != NULL) {
        cont += log_obter_contagem_por_classe(&esq, classe);
        if ((*l)->classe == classe)
            cont++;
        cont += log_obter_contagem_por_classe(&dir, classe);
    }

    return cont;
}

float log_media_por_classe(Log **l, int classe) {
    /**Descrição: Retorna a média do tempo de espera total por cliente de uma classe
     * Autor: Diego
     * 
     * Args : [
     *      l : Log **,
     *      classe : int
     * ]
     * 
     * Returns: media : float
     * 
    */
    int soma, contagem;
    float media;

    // Média simples
    soma = log_obter_soma_por_classe(l, classe);
    contagem = log_obter_contagem_por_classe(l, classe);
    media = ((float) soma)/((float) contagem);

    return media;
}