#include <stdlib.h>
#include "fila_fifo.h"

void f_inicializar(Fila_FIFO **F){
    (*F)->prox = NULL;
}
int f_inserir(Fila_FIFO **F, int chave, int valor){
    Fila_FIFO *novo, *aux;

    if( (*F)->prox == NULL){
        (*F)->prox = novo;
        return 1;

    aux = (*F)->prox;

    while( aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;

}