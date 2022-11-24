#include <stdio.h>
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
     * Returns: 0 - key duplication or insufficient memory
     *          1 - insertion success.
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
     * Returns: -1 empty queue
     *          key's number of next element.
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
     * Returns: -1 - empty queue
     *          key's number of next element
     * 
    */  
    Fila_FIFO *aux;
    aux = (*F);
    
    if(aux == NULL)
        return -1;
    return aux->chave;  
}
int f_consultar_proxima_valor(Fila_FIFO **F){
    /**Descrição: consulta o valor do nó cabe;a
     * Autor: Gabriel
     * 
     * Args: F : Fila_FIFO **
     * 
     * Returns: -1 - empty queue
     *          value of next element
     * 
    */  
    Fila_FIFO *aux;
    aux = (*F);
    
    if(aux == NULL)
        return -1;
    return aux->valor;  
}

void print_fila(Fila_FIFO *F){
    Fila_FIFO *aux = F;
    while (aux != NULL)
    {
        printf("chave: %d\nvalor: %d\n", aux->chave, aux->valor);
        aux = aux->prox;
    }
}

int main(){
    Fila_FIFO *fila;
    f_inicializar(&fila);
    
    for (int i = 1; i<3; i++){
        if(f_inserir(&fila, i, 10+i)){
        } else {
            puts("repetido");
            return EXIT_FAILURE;
        }
    }
    print_fila(fila);
    printf("\n%d\n\n", f_consultar_proxima_valor(&fila));
    return EXIT_SUCCESS;
}