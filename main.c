#include <stdio.h>
#include "./logtree.h"

int main() {
    Log *raiz;
    log_inicializar(&raiz);
    log_registrar(&raiz, 10, 10, 10, 10);
    log_registrar(&raiz, 10, 10, 30, 10);
    log_registrar(&raiz, 10, 10, 30, 10);
    log_registrar(&raiz, 10, 20, 40, 10);
    log_registrar(&raiz, 10, 20, 40, 10);
    printf("%f\n", log_media_por_classe(&raiz, 10));
    return 1;
}
