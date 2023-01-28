#include "fila_fifo.h"

#ifndef escalonador_h
#define escalonador_h

typedef struct _escalonador {
    int caixas;
    int delta_t;
    int atual; //Indica a classe atual do contador 
    int cont;
    int num [5];
    Fila_FIFO *fila[5];
} Escalonador;

void e_inicializar (Escalonador *, int, int, int, int, int, int, int);
int e_inserir_por_fila (Escalonador *, int, int, int);
void _e_atualizar_atual(Escalonador *);
int e_obter_prox_num_conta(Escalonador *);
int e_consultar_prox_num_conta (Escalonador *);
int e_consultar_prox_qtde_oper (Escalonador *);
int e_consultar_prox_fila (Escalonador *);
int e_consultar_qtde_clientes (Escalonador *);
int e_consultar_tempo_prox_cliente (Escalonador *);
int e_conf_por_arquivo (Escalonador *, char *);
void e_rodar (Escalonador *, char *, char *);

#endif