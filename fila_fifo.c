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
    /**Descrição: Registra um cliente na fila
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
    if(*F == NULL) *F = temp;           // Caso a vila esteja vazia, o cliente vai para a 1a posição
    else{
        while( aux->prox != NULL){      // Caso contrário, fazemos a análise ate achar o último ponto da fila
            if( aux->chave == chave)    // Caso a chave do cliente já esteja cadastrada, retornamos 0
                return 0;
            aux = aux->prox;            
        }
        aux->prox = temp;               // Cadastramos o cliente na ultima posição da fila
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
    key = aux->chave;   // Retemos a chave da 1a posição da fila - a qual iremos remover
    (*F) = (*F)->prox;  // Passamos a começar a fila apos a primeira posição, ou seja, removendo a 1a posição e tornando a 2a posição como inicializadora
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
    return aux->chave;  // Retornamos a 1a chave da fila (nó cabeça)
}

int f_consultar_proximo_valor(Fila_FIFO **F){
    /**Descrição: consulta o valor do nó cabeça
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
    return aux->valor;  // Retornamos o 1o valor atribuído a fila (valor do nó cabeça)
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
    while(aux != NULL){     // Usamos este laço para achar a última posição da fila
        aux = aux->prox;
        num++;              // Passando posição por posição, vamos contabilizando o número de elementos por cada passagem
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
    for(i = 0; i<(posicao-1); i++)      // Vamos até a posição anterior a posição requerida de fato
        aux = aux->prox;                // Atualizamos o valor do auxiliar para o próximo
    return aux->chave;                  // Retornamos a chave da ésima posição
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
    for(i = 0; i<(posicao-1); i++)      // Vamos até a posição anterior a posição requerida de fato
        aux = aux->prox;                // Atualizamos o valor do auxiliar para o próximo
    return aux->valor;                  // Retornamos o valor da chave na ésima posição
}