#include "escalonador.h"
#include "fila_fifo.h"
#include "logtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME_CLASSE 8
#define MAX_BUFFER_STR 10000

void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5){
    /**Descrição: Inicializa o escalonador
     * Autor: Diego
     * 
     * Args: [
     *      e : Escalonador *,
     *      caixas : int,
     *      delta_t : int,
     *      n_1 : int,
     *      n_2 : int,
     *      n_3 : int,
     *      n_4 : int,
     *      n_5 : int
     * ]
     * 
     * Returns: None
     * 
    */
    
    e->caixas = caixas;
    e->delta_t = delta_t;
    e->num[0] = n_1;
    e->num[1] = n_2;
    e->num[2] = n_3;
    e->num[3] = n_4;
    e->num[4] = n_5;
    f_inicializar(&(e->fila[0]));
    f_inicializar(&(e->fila[1]));
    f_inicializar(&(e->fila[2]));
    f_inicializar(&(e->fila[3]));
    f_inicializar(&(e->fila[4]));
    e->atual = 1;
    e->cont = n_1;
}

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes) {
    /**Descrição: Insere um cliente no escalonador
     * Autor: Diego
     * 
     * Args : [
     *      e : Escalonador *,
     *      classe : int,
     *      num_conta : int,
     *      qtde_operacoes : int
     * ]
     * 
     * Returns : int
    */
    
    f_inserir(&(e->fila[classe-1]), num_conta, qtde_operacoes);
    return 1;
}

int e_obter_prox_num_conta(Escalonador *e) {
    /**Descrição: Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento, retirando-o da sua respectiva fila
     * Autor: Tobias
     * 
     * Args: e : Escalonador *
     * 
     * Returns: conta : int
     * 
    */
    int conta = f_obter_proxima_chave(&(e->fila[e->atual -1])); // Atribuímos o valor da conta do cidadão baseando-se na chave que ele recebeu
    e->cont--; // Diminuímos o contador visto que f_obter_proxima_chave já removeu o cidadão
    if (e->cont == 0){ // Caso verdade, acabamos de retirar o último da fila, precisamos reinicializar o contador
        e->atual++; // Aumentamos a classe, visto que analisaremos outra fila
        if (e->atual == 6){ // Caso verdade, chegamos na última classe
            e->atual = 1; // Com isso, retornamos a primeira classe e repetiremos o processo
        }
        e->cont = e->num[e->atual-1]; // Nosso contador recebe o novo número específico a nova fila
    }
    return conta; // Retornamos a conta, cumprindo o dever de nossa função
}

int e_consultar_prox_num_conta (Escalonador *e) {
    /**Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento, sem retirá-lo da sua respectiva fila
     * Autor: Tobias
     * 
     * Args: e : Escalonador *
     * 
     * Returns: conta : int
     * 
    */
    int conta = f_consultar_proxima_chave(&(e->fila[e->atual -1])); // Atribuímos o valor da conta do cidadão baseando-se na chave que ele recebeu
    return conta; // Retornamos a conta, cumprindo o dever de nossa função
}

int e_consultar_prox_qtde_oper (Escalonador *e) {
    /** Descrição: Retorna a quantidade de operações bancárias que o próximo cliente das filas pretende realizar com o caixa, sem retirá-lo da sua respectiva fila
     * Autor: Tobias
     * 
     * Args: e : Escalonador *
     * 
     * Returns: operacoes : int
     * 
    */
    int operacoes = f_consultar_proximo_valor(&(e->fila[e->atual-1])); // Atribuímos o valor dentro do nó (quant. de operações) para o inteiro "operacoes"
    return operacoes;
}

int e_consultar_prox_fila (Escalonador *e) {
    /**Descrição: Retorna a próxima fila que será atendida de acordo com a Disciplina de Atendimento
     * Autor: Tobias
     * 
     * Args: e : Escalonador *
     * 
     * Returns: f : int
     * 
    */
    int f = e->atual; // Atribuímos o valor da fila atual sem correção de valores (sem considerar começo em f[0]), para obtermos já a resposta da fila acrescida em 1
    return f;
}

int e_consultar_qtde_clientes (Escalonador *e) {
    /**Descrição: Retorna a quantidade total (soma) de clientes esperando atendimento em todas as filas
     * Autor: Tobias
     * 
     * Args: e : Escalonador *
     * 
     * Returns: qtde_clientes : int
     * 
    */
    int qtde_clientes = 0, i; 
    for (i = 0; i < 5; i++) {
        qtde_clientes += f_num_elementos(&(e->fila[i]));
    } // Somamos a quantidade de clientes em todas as filas
    return qtde_clientes;
}

int e_consultar_tempo_prox_cliente (Escalonador *e) {
    /**Descrição: Retorna o tempo necessário para que o próximo cliente a ser atendido realize todas as operações financeiras que deseja, sem retirá-lo da sua respectiva fila. Retornar -1 caso não tenha nenhum cliente em todas as filas.
     * Autor: Tobias
     * 
     * Args: e : Escalonador *
     * 
     * Returns: timer : int
     * 
    */
    if (e->cont == 0) {
        return -1;
    } else { // Lembre: o timer é definido para chamar outro cliente dentro de M × delta_t min.
        int timer = (e->delta_t*e_consultar_prox_qtde_oper(e)); // Fazemos a operacao M*delta_t e atribuímos ao timer
        return timer; 
    }
}

int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf) {
    /**Descrição: Lê um arquivo texto de configuração e atualiza os dados do escalonador
     * Autor: Diego
     * 
     * Args: [
     *      e : Escalonador *,
     *      nome_arq_conf : char *
     * ]
     * 
     * Returns: int
     * 
    */
    int i = 0, temp_conta, temp_op, temp_classe;
    int temp_caixa, temp_dt, temp_n1, temp_n2, temp_n3, temp_n4, temp_n5;
    FILE *fp;
    char c[MAX_BUFFER_STR], nome_classe[MAX_NOME_CLASSE];

    fp = fopen(nome_arq_conf, "r");
    if (fp == NULL)
        return 0;
    
    while ((fgets(c, sizeof(c), fp)) != NULL) {
        if (i == 0) {
            sscanf(c, "qtde de caixas = %d", &temp_caixa);
        } else if (i == 1) {
            sscanf(c, "delta t = %d", &temp_dt);
        } else if (i == 2) {
            sscanf(c, "disciplina de escalonamento = {%d,%d,%d,%d,%d}", &temp_n1, &temp_n2, &temp_n3, &temp_n4, &temp_n5);
            e_inicializar(e, temp_caixa, temp_dt, temp_n1, temp_n2, temp_n3, temp_n4, temp_n5);
        } else {
            sscanf(c, "%s - conta %d - %d operacao(oes)", nome_classe, &temp_conta, &temp_op);
            if (strcmp(nome_classe, "Premium") == 0) {
                temp_classe = 1;
            } else if (strcmp(nome_classe, "Ouro") == 0) {
                temp_classe = 2;
            } else if (strcmp(nome_classe, "Prata") == 0) {
                temp_classe = 3;
            } else if (strcmp(nome_classe, "Bronze") == 0) {
                temp_classe = 4;
            } else if (strcmp(nome_classe, "Leezu") == 0) {
                temp_classe = 5;
            } else {
                return 0;
            }
            e_inserir_por_fila(e, temp_classe, temp_conta, temp_op);
        }
        i++;
    }
    return 1;
}

void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out) {
    /**Descrição: Realiza a simulação e salva em um arquivo de saída
     * Autor: Diego, Gabriel e Tobias
     * 
     * Args: [
     *      e : Escalonador *,
     *      nome_arq_in : char *,
     *      nome_arq_out : char *
     * ]
     * 
     * Returns: None
     * arquivo 
    */
    Log *registrador;
    FILE *arq_out;
    int timer = 0, maior = 0;
    int caixas[10], operacoes[5], valores[10];
    int i, qtde_operacoes, conta, classe, check, atual;
    float tempo_medias[5];

    arq_out = fopen(nome_arq_out, "w");

    e_conf_por_arquivo(e, nome_arq_in);
    log_inicializar(&registrador);

    check = e_consultar_prox_num_conta(e);

    for (i = 0; i < e->caixas; i++) {
        caixas[i] = 1;
        valores[i] = 0;
    }

    for (i = 0; i < 5; i++) {
        operacoes[i] = 0;
    }

    while (check != -1) {
        for (i = 0; i < e->caixas; i++){
            caixas[i] = caixas[i] - 1;
            if (caixas[i] == 0){
                classe = e->atual;
                qtde_operacoes = e_consultar_prox_qtde_oper(e);
                conta = e_obter_prox_num_conta(e);
                if (conta == -1){
                    conta = e_obter_prox_num_conta(e);
                    classe = e->atual;
                }
                if (conta != -1 && conta != 0){
                    operacoes[classe - 1] = operacoes[classe - 1] + qtde_operacoes;
                    atual = i + 1;
                    log_registrar(&registrador, conta, classe, timer, atual);
                    switch (classe) {
                        case 1:
                            fprintf(arq_out, "T = %d min: Caixa %d chama da categoria Premium cliente da conta %d para realizar %d operacao(oes).\n", timer, atual, conta, qtde_operacoes);
                            break;
                        case 2:
                            fprintf(arq_out, "T = %d min: Caixa %d chama da categoria Ouro cliente da conta %d para realizar %d operacao(oes).\n", timer, atual, conta, qtde_operacoes);
                            break;
                        case 3:
                            fprintf(arq_out, "T = %d min: Caixa %d chama da categoria Prata cliente da conta %d para realizar %d operacao(oes).\n", timer, atual, conta, qtde_operacoes);
                            break;
                        case 4:
                            fprintf(arq_out, "T = %d min: Caixa %d chama da categoria Bronze cliente da conta %d para realizar %d operacao(oes).\n", timer, atual, conta, qtde_operacoes);
                            break;
                        case 5:
                            fprintf(arq_out, "T = %d min: Caixa %d chama da categoria Comum cliente da conta %d para realizar %d operacao(oes).\n", timer, atual, conta, qtde_operacoes);
                            break;
                        default:
                            break;
                    }
                    caixas[i] = qtde_operacoes*e->delta_t;
                    valores[i] = valores[i] + 1;
                }
            }
            check = e_consultar_prox_num_conta(e);
        }
        timer++;
    } timer--;

    for (i = 0; i < e->caixas; i++) {
        if (maior < caixas[i]) {
            maior = caixas[i];
        }
    }

    timer = timer + maior;

    for (i = 0; i < 5; i++) {
        tempo_medias[i] = ((float) operacoes[i])/((float) log_obter_contagem_por_classe(&registrador, i+1));
    }

    fprintf(arq_out, "Tempo total de atendimento: %d minutos.\n", timer);
    fprintf(arq_out,"Tempo medio de espera dos %d clientes Premium: %.2f\n", log_obter_contagem_por_classe(&registrador, 1), log_media_por_classe(&registrador, 1));
    fprintf(arq_out,"Tempo medio de espera dos %d clientes Ouro: %.2f\n", log_obter_contagem_por_classe(&registrador, 2), log_media_por_classe(&registrador, 2));
    fprintf(arq_out,"Tempo medio de espera dos %d clientes Prata: %.2f\n", log_obter_contagem_por_classe(&registrador, 3), log_media_por_classe(&registrador, 3));
    fprintf(arq_out,"Tempo medio de espera dos %d clientes Bronze: %.2f\n", log_obter_contagem_por_classe(&registrador, 4), log_media_por_classe(&registrador, 4));
    fprintf(arq_out,"Tempo medio de espera dos %d clientes Leezu: %.2f\n", log_obter_contagem_por_classe(&registrador, 5), log_media_por_classe(&registrador, 5));    
    fprintf(arq_out,"Quantidade media de operacoes por cliente Premium = %.2f\n", tempo_medias[0]);
    fprintf(arq_out,"Quantidade media de operacoes por cliente Ouro = %.2f\n", tempo_medias[1]);
    fprintf(arq_out,"Quantidade media de operacoes por cliente Prata = %.2f\n", tempo_medias[2]);
    fprintf(arq_out,"Quantidade media de operacoes por cliente Bronze = %.2f\n", tempo_medias[3]);
    fprintf(arq_out,"Quantidade media de operacoes por cliente Leezu = %.2f\n", tempo_medias[4]);

    for (i = 0; i < e->caixas; i++){
        fprintf(arq_out,"O caixa de número %d atendeu %d clientes.\n", i+1, valores[i]);
    }
}