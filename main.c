/*
*----------------------------*
| Autores                    |
*----------------------------*
| ArtroxGabriel              |
| nikrs14                    |
| Tobnobre                   |
*----------------------------*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./logtree.h"
#include "./fila_fifo.h"
#include "./escalonador.h"

#define MAX_IO 20

int main(int narg, char * argv[]) {
    Escalonador e;
    int numero;
    char entrada[MAX_IO], saida[MAX_IO];
    if(narg == 1){
        puts("Nenhum parametro encontrado.");
        return EXIT_FAILURE;
    }
    numero = atoi(argv[1]);

    sprintf(entrada, "entrada-%.4d.txt", numero);
    sprintf(saida, "saida-%.4d.txt", numero);

    e_rodar(&e, entrada, saida);
    return EXIT_SUCCESS;
}