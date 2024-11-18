/**
 * Arquivo: queueTAD_lse.c
 * Versão : 1.0
 * Data   : 2024-11-02 20:49
 * -------------------------
 * Este arquivo implementa a interface queueTAD.h através do uso de uma lista
 * simplesmente encadeada (LSE) sem tamanho máximo definido (a fila pode ser
 * aumentada indefinidamente, a depender apenas dos recursos computacionais).
 *
 * Baseado em: Programming Abstractions in C, de Eric S. Roberts.
 *             Capítulo 10: Linear Structures (pg. 433-439).
 *
 * Prof.: Abrantes Araújo Silva Filho (Computação Raiz)
 *            www.computacaoraiz.com.br
 *            www.youtube.com.br/computacaoraiz
 *            github.com/computacaoraiz
 *            twitter.com/ComputacaoRaiz
 *            www.linkedin.com/company/computacaoraiz
 *            www.abrantes.pro.br
 *            github.com/abrantesasf
 */

/*** Includes ***/

#include "queueTAD.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*** Constantes Simbólicas ***/

/*** Variáveis e Constantes Globais ***/

/*** Tipos de Dados ***/

/**
 * Tipo: struct celulaTCD
 * ----------------------
 * Define uma célula (nó) da lista encadeada simples (LSE) que implementará a
 * fila. O tipo concreto é o "celulaTCD"; também é criado um tipo "abstrato" com
 * o nome de "celulaTAD" (na verdade não é um tipo abstrato real, pois a
 * implementação concreta está visível, mas isso simplificará a implementação).
 */

struct celulaTCD
{
    elementoT elemento;
    struct celulaTCD *proximo;
};

typedef struct celulaTCD *celulaTAD;

/**
 * Tipo: struct queueTCD
 * ---------------------
 * Este tipo define a representação concreta da fila. Esta implementação utiliza
 * uma lista simplesmente encadeada (LSE) para armazenar so dados, e contém
 * apenas os ponteiros "início" e "fim" da lista. Como a implementaçao é através
 * de uma LSE, a lista é considerada dinâmica e não tem tamanho máximo definido.
 * O número de elementos atualmente na fila também é armazenado para facilitar
 * a consulta dessa informação. Nesta implementação:
 *
 *     a) O próximo elemento a ser enfileirado será colocado após a última
 *        célula da lista, apontada pelo ponteiro "fim"; e
 *     b) O próximo elemento a ser desenfileirado será a primeira célula da
 *        lista, apontada pelo ponteiro "inicio".
 */

struct queueTCD
{
    celulaTAD inicio;
    celulaTAD fim;
    size_t nelem;
};

/**
 * Tipo: celula_status
 * -------------------
 * Define uma enumeração com os possíveis status de retorno das funções privadas
 * desta implementação, para o tratamento das celulaTAD. Inclui o status de
 * sucesso e os diversos status de erro que podem ser retornados. Os seguintes
 * membros estão definidos:
 *
 *     CELULA_OK                : operação realizada com sucesso
 *     CELULA_ERRO_CELULA       : célula inválida
 *     CELULA_ERRO_ALOCACAO     : erro na alocação/liberação de memória
 *     CELULA_ERRO_ARGUMENTO    : argumento inválido
 */

typedef enum
{
    CELULA_OK,
    CELULA_ERRO_CELULA,
    CELULA_ERRO_ALOCACAO,
    CELULA_ERRO_ARGUMENTO
} celula_status;

/*** Declarações de Suprogramas Privados ***/

static celulaTAD criar_celula (void);
static celula_status remover_celula (celulaTAD *celula);

/*** Definições de Subprogramas Exportados ***/

/**
 * Função: CRIAR_QUEUE
 * Uso: queue = criar_queue( );
 * ----------------------------
 * Usa calloc para criar a fila e ajusta os ponteiros e a contagem de elementos.
 * Retorna NULL em caso de erro, ou o ponteiro para a fila em caso de sucesso.
 */

queueTAD
criar_queue (void)
{
    queueTAD Q = calloc(1, sizeof(struct queueTCD));
    if (Q == NULL)
        return NULL;

    Q->inicio = Q->fim = NULL;
    Q->nelem = 0;
    return Q;
}

/**
 * Função: REMOVER_QUEUE
 * Uso: status = remover_queue(&queue);
 * ------------------------------------
 * Verifica se o ponteiro e a queue apontada são válidos e libera toda a memória
 * da queue. Retorna queue_status apropriado.
 */

queue_status
remover_queue (queueTAD *queue)
{
    if (queue == NULL)
        return QUEUE_ERRO_ARGUMENTO;
    else if (*queue == NULL)
        return QUEUE_ERRO_QUEUE;

    celulaTAD atual, proximo;
    celula_status status;
    
    atual = (*queue)->inicio;
    while (atual != NULL)
    {
        proximo = atual->proximo;
        status = remover_celula(&atual);
        if (status != CELULA_OK)
            return QUEUE_ERRO_ALOCACAO;
        atual = proximo;
    }
    
    free(*queue);
    *queue = NULL;
    
    return QUEUE_OK;
}

/**
 * Função: ENQUEUE
 * Uso: status = enqueue(queue, elemento);
 * ---------------------------------------
 * Verifica se a queue é válida e enfileira o elemento informado. Retorna o
 * queue_status apropriado.
 */

queue_status
enqueue (queueTAD queue, const elementoT elemento)
{
    if (queue == NULL)
        return QUEUE_ERRO_QUEUE;
    else if (elemento == NULL)
        return QUEUE_ERRO_ARGUMENTO;

    celulaTAD nova = criar_celula();
    if (nova == NULL)
        return QUEUE_ERRO_ALOCACAO;

    nova->elemento = elemento;
    nova->proximo = NULL;

    if (queue->inicio == NULL)
    {
        queue->inicio = nova;
    }
    else
    {
        queue->fim->proximo = nova;
    }
    queue->fim = nova;
    queue->nelem += 1;
    
    return QUEUE_OK;
}

/**
 * Função: DEQUEUE
 * Uso: status = dequeue(queue, &elemento);
 * ----------------------------------------
 * Verifica se a queue é válida e desenfileira o elemento no início da fila. O
 * elemento é colocado no endereço apontado pelo ponteiro "elemento". Retorna o
 * queue_status apropriado.
 */

queue_status
dequeue (queueTAD queue, elementoT *elemento)
{
    if (queue == NULL)
        return QUEUE_ERRO_QUEUE;
    else if (elemento == NULL)
        return QUEUE_ERRO_ARGUMENTO;
    else if (queue->nelem == 0)
        return QUEUE_ERRO_VAZIA;

    *elemento = queue->inicio->elemento;

    celulaTAD temp = queue->inicio;
    celula_status status;
    
    queue->inicio = temp->proximo;
    
    status = remover_celula(&temp);
    if (status != CELULA_OK)
        return QUEUE_ERRO_ALOCACAO;

    if (queue->inicio == NULL)
        queue->fim = NULL;
    
    queue->nelem -= 1;
    
    return QUEUE_OK;
}

/**
 * Função: VAZIA
 * Uso: if (vazia(queue, &esta_vazia) == QUEUE_OK && esta_vazia == true) . . .
 * ---------------------------------------------------------------------------
 * Recebe uma "queue" e um PONTEIRO para um booleano "esta_vazia", e retorna
 * valores que nos permitem identificar se a fila está vazia ou não (ou, se
 * ocorrer algum erro, permitem identificar esse erro).
 */

queue_status
vazia (const queueTAD queue, bool *esta_vazia)
{
    if (queue == NULL)
        return QUEUE_ERRO_QUEUE;
    else if (esta_vazia == NULL)
        return QUEUE_ERRO_ARGUMENTO;

    *esta_vazia = queue->nelem == 0;
    return QUEUE_OK;
}

/**
 * Função: CHEIA
 * Uso: if (cheia(queue, &esta_cheia) == QUEUE_OK && esta_cheia == true) . . .
 * ---------------------------------------------------------------------------
 * Recebe uma "queue" e um PONTEIRO para um booleano "esta_vazia", e retorna
 * valores que nos permitem identificar se a fila está vazia ou não (ou, se
 * ocorrer algum erro, permitem identificar esse erro). Como a implementação é
 * com uma LSE, a fila nunca estará cheia, ou seja, terá tamanho ilimitado.
 */

queue_status
cheia (const queueTAD queue, bool *esta_cheia)
{
    if (queue == NULL)
        return QUEUE_ERRO_QUEUE;
    else if (esta_cheia == NULL)
        return QUEUE_ERRO_ARGUMENTO;

    *esta_cheia = false;
    return QUEUE_OK;
}

/**
 * Função: NUM_ELEMENTOS
 * Uso: status = num_elementos(queue, &nelem);
 * ------------------------------------------
 * Recebe uma "queue" e armazena no local apontado pelo ponteiro "nelem" o
 * tamanho efetivo da fila ou seja, a quantidade atual de elementos.
 */

queue_status
num_elementos (const queueTAD queue, size_t *nelem)
{
    if (queue == NULL)
        return QUEUE_ERRO_QUEUE;
    else if (nelem == NULL)
        return QUEUE_ERRO_ARGUMENTO;

    *nelem = queue->nelem;
    return QUEUE_OK;
}

/**
 * Função: INFO
 * Uso: status = info(queue, &din, &tamax);
 * ---------------------------------------;
 * Esta função não faz parte dos comportamentos normais esperados para uma fila
 * mas é definida nesta interface para que o cliente possa obter diversas
 * informações sobre a fila e sua implementação interna.
 */

queue_status
info (const queueTAD queue, bool *din, int *tamax)
{
    if (queue == NULL)
        return QUEUE_ERRO_QUEUE;
    else if (din == NULL)
        return QUEUE_ERRO_ARGUMENTO;
    else if (tamax == NULL)
        return QUEUE_ERRO_ARGUMENTO;

    *din = true;
    *tamax = -1;
    return QUEUE_OK;
}

/**
 * Função: VER_ELEMENTO
 * Uso: status = ver_elemento(queue, posicao, &elemento);
 * ------------------------------------------------------
 * Retorna o elemento armazenado em "posicao", sem desenfileirar o elemento.
 * Como a posição de início não é fixa, a posição retornada depende de onde
 * está o começo da fila, ou seja: o cliente informará sempre uma posição
 * absoluta, mas a função utilizará a posição relativa a partir do índie de
 * início da fila.
 */

#ifdef debug
queue_status
ver_elemento (const queueTAD queue, const size_t posicao, elementoT *elemento)
{
    if (queue == NULL)
        return QUEUE_ERRO_QUEUE;
    else if (elemento == NULL)
        return QUEUE_ERRO_ARGUMENTO;
    else if (posicao >= queue->nelem)
        return QUEUE_ERRO_POSICAO;

    celulaTAD temp = queue->inicio;
    for (size_t i = 0; i < posicao; i++)
        temp = temp->proximo;
    *elemento = temp->elemento;
    
    return QUEUE_OK;
}
#endif

/*** Definições de Subprogramas Privados ***/

/**
 * Função: CRIAR_CELULA
 * Uso: celula = criar_celula( );
 * ------------------------------
 * Aloca a memória e cria uma nova célula para a LSE. Retorna o ponteiro para a
 * célula alocada, ou NULL em caso de erro.
 */

static celulaTAD
criar_celula (void)
{
    celulaTAD C = calloc(1, sizeof(struct celulaTCD));
    if (C == NULL)
        return NULL;

    C->proximo = NULL;
    return C;
}

/**
 * Função: REMOVER_CELULA
 * Uso: status = remover_celula(&celula);
 * --------------------------------------
 * Recebe um ponteiro para uma celulaTAD e faz a liberação de memória dessa
 * célula, retornando CELULA_OK. Em caso de erro, retorna o celula_status
 * correspondente.
 */

static celula_status
remover_celula (celulaTAD *celula)
{
    if (celula && *celula)
    {
        free(*celula);
        *celula = NULL;
        return CELULA_OK;
    }

    return CELULA_ERRO_ALOCACAO;
}

/**
 * Função: PRIORITY_ENQUEUE
 * Uso: status = priority_enqueue(queue, elemento, prioridade);
 * ------------------------------------------------------------
 * Recebe uma "queue", um "elemento" e sua "prioridade", e insere o elemento
 * na posição correta da fila, com base na prioridade (menores valores de
 * prioridade são tratados como mais prioritários).
 * Os possíveis retornos são:
 *
 *     a) QUEUE_OK: operação realizada com sucesso;
 *     b) QUEUE_ERRO_QUEUE: queue inválida;
 *     c) QUEUE_ERRO_ARGUMENTO: elemento ou prioridade inválidos.
 */
queue_status
priority_enqueue(queueTAD queue, const elementoT elemento, int prioridade)
{
    if (queue == NULL) return QUEUE_ERRO_QUEUE;
    if (queue == NULL) return QUEUE_ERRO_ARGUMENTO;

    celulaTAD nova = criar_celula();
    if (nova == NULL) return QUEUE_ERRO_ALOCACAO;

    nova->elemento = elemento;
    nova->proximo = NULL;

    if (queue->inicio == NULL)
    {
        queue->inicio = queue->fim = nova;
        queue->nelem++;

        return QUEUE_OK;
    }

    if (((int *)queue->inicio->elemento)[1] > prioridade)
    {
        nova->proximo = queue->inicio;
        queue->inicio = nova;
        queue->nelem++;

        return  QUEUE_OK;
    }

    celulaTAD atual = queue->inicio;
    while (atual->proximo != NULL && ((int *)atual->proximo->elemento)[1] <= prioridade)
    {
        atual = atual->proximo;
    }

    nova->proximo = atual->proximo;
    atual->proximo = nova;

    if (nova->proximo == NULL) queue->fim = nova;
    
    queue->nelem++;
    
    return QUEUE_OK;
}
