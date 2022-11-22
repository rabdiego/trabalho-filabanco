#include "./logtree.h"

int main() {
    Log **raiz;
    log_inicializar(raiz);
    log_registrar(raiz, 10, 10, 10, 10);
    return 1;
}
