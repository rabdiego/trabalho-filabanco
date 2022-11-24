#include <stdlib.h>
#include "fila_fifo.h"

void f_inicializar(Fila_FIFO **F){
    /**Descrição: Inicializa um registrador
     * Autor: Gabriel
     * 
     * Args: F : Fila_FIFO **
     * 
     * Returns: None
     * 
    */
    (*F) = NULL;
}

int f_inserir(Fila_FIFO **F, int chave, int valor){
    /**Descrição: Registra um cliente no fila
     * Autor: Gabriel
     * 
     * Args: [
     *      F : Fila_FIFO **,
     *      chave : int,
     *      valor : int,
     * ]
     * 
     * Returns: 0 : key duplication or insufficient memory
     *          1 : insertion success.
     * 
    */
    Fila_FIFO *aux, *temp = (Fila_FIFO *) malloc(sizeof(Fila_FIFO));
    if(temp == NULL)
        return 0;
    temp->chave = chave;
    temp->valor = valor;
    temp->prox = NULL;
    aux = *F;
    if(*F == NULL) *F = temp;
    else{
        while( aux->prox != NULL){
            if( aux->chave == chave)
                return 0;
            aux = aux->prox;
        }
        aux->prox = temp;
    }
    return 1;
}

int f_obter_proxima_chave(Fila_FIFO **F){
    /**Descrição: Obtem a proxima chave da fila e a remove após.
     * Autor: Gabriel
     * 
     * Args: [
     *      F : Fila_FIFO **,
     * ]
     * 
     * Returns: -1  : empty queue
     *          key : key's number of next element.
     * 
    */
    int key;
    Fila_FIFO *aux;
    aux = (*F);
    
    if(aux == NULL)
        return -1;
    key = aux->chave;
    (*F) = (*F)->prox;
    free(aux);
    return key;  
}

int f_consultar_proxima_chave(Fila_FIFO **F){
    /**Descrição: consulta o valor do nó cabeça
     * Autor: Gabriel
     * 
     * Args: F : Fila_FIFO **
     * 
     * Returns: -1         : empty queue
     *          aux->chave : key's number of next element
     * 
    */  
    Fila_FIFO *aux;
    aux = (*F);
    
    if(aux == NULL)
        return -1;
    return aux->chave;  
}

int f_consultar_proximo_valor(Fila_FIFO **F){
    /**Descrição: consulta o valor do nó cabe;a
     * Autor: Gabriel
     * 
     * Args: F : Fila_FIFO **
     * 
     * Returns: -1          : empty queue
     *          aux->valor : value of next element
     * 
    */  
    Fila_FIFO *aux;
    aux = (*F);
    
    if(aux == NULL)
        return -1;
    return aux->valor;  
}

int f_num_elementos(Fila_FIFO **F){
    /**Descrição: Retorna o numero de elementos na fila
     * Autor: Gabriel
     * 
     * Args : [
     *      F : Fila_FIFO **,
     * ]
     * 
     * Returns: num : int
     * 
    */
    int num = 0;
    Fila_FIFO *aux = *F;
    while(aux != NULL){
        aux = aux->prox;
        num++;
    }
    return num;
}

int f_consultar_chave_por_posicao (Fila_FIFO **F, int posicao){
    /**Descrição: Retorna a chave do posicao-ésimo elemento da fila.
     * Autor: Gabriel
     * 
     * Args : [
     *      F : Fila_FIFO **,
     *      posicao : int;
     * ]
     * 
     * Returns: -1 : int
     *          aux->chave : chave da posicao-ésimo
     * 
    */
    int i;
    Fila_FIFO *aux = *F;

    if (posicao > f_num_elementos(F))
        return -1;
    for(i = 0; i<(posicao-1); i++)
        aux = aux->prox;
    return aux->chave;
}

int f_consultar_valor_por_posicao (Fila_FIFO **F, int posicao){
    /**Descrição: Retorna a valor da chave do posicao-ésimo elemento da fila.
     * Autor: Gabriel
     * 
     * Args : [
     *      F : Fila_FIFO **,
     *      posicao : int;
     * ]
     * 
     * Returns: -1 : int
     *          aux->valor : valor da chave do posicao-ésimo
     * 
    */
    int i;
    Fila_FIFO *aux = *F;

    if (posicao > f_num_elementos(F))
        return -1;
    for(i = 0; i<(posicao-1); i++)
        aux = aux->prox;
    return aux->valor;
}