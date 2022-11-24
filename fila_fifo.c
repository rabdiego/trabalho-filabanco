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
    /**Descrição: Registra um cliente no registrador
     * Autor: Gabriel
     * 
     * Args: [
     *      F : Fila_FIFO **,
     *      chave : int,
     *      valor : int,
     * ]
     * 
     * Returns: 0 key duplication or insufficient memory
     *          1 insertion success.
     * 
    */
    Fila_FIFO *aux, *temp = (Fila_FIFO *) malloc(sizeof(Fila_FIFO));
    if(temp == NULL)
        return 0;
    temp->chave = chave;
    temp->valor = valor;
    temp->prox = *F;
    aux = *F;
    while( aux != NULL){
        if( aux->chave == chave)
            return 0;
        aux = aux->prox;
    }
    *F = temp;
    return 1;
}
