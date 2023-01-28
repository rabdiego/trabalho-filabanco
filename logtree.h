#ifndef logtree_h
#define logtree_h

typedef struct _log {
    int conta;
    int classe;
    int timer;
    int caixa;
    struct _log *esq;
    struct _log *dir;
} Log;

void log_inicializar(Log **);
void log_registrar(Log **, int, int, int, int);
int log_obter_soma_por_classe(Log **, int);
int log_obter_contagem_por_classe(Log **, int);
float log_media_por_classe(Log **, int);

#endif