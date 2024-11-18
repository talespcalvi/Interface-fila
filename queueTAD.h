/**
 * Arquivo: queueTAD.h
 * Versão : 1.0
 * Data   : 2024-10-31 21:43
 * -------------------------
 * Este arquivo define a interface queueTAD.h, uma FILA GENÉRICA (cujos
 * elementos são do tipo "void *") que permite enfileirar qualquer tipo
 * de dado.
 *
 * Baseado em: Programming Abstractions in C, de Eric S. Roberts.
 *             Capítulo 10: Linear Structures (pg. 424-429).
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

/*** Inicia Boilerplate da Interface ***/

#ifndef _QUEUETAD_H
#define _QUEUETAD_H

/*** Includes ***/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*** Constantes Simbólicas ***/

/*** Tipos de Dados ***/

/**
 * Tipo: elementoT
 * ---------------
 * O tipo elementoT é utilizado nesta inferface para indicar o tipo de valor que
 * será armazenado na fila. Por padrão a fila é utilizada para armazenar valores
 * do tipo "void *" (tornando a fila genérica), mas isso pode ser modificado
 * alterando-se a definção na linha abaixo.
 */

typedef void *elementoT;

/**
 * Tipo abstrato: queueTAD
 * -----------------------
 * O tipo "queueTAD" é um tipo abstrado de dado para representar uma fila. É
 * definido como um ponteiro para queueTCD (o tipo concreto que implementa a
 * fila), que está disponível apenas para a implementação, não para os clientes.
 */

typedef struct queueTCD *queueTAD;

/**
 * Tipo: queue_status
 * ------------------
 * Define uma enumeração com os possíveis status de retorno das funções desta
 * interface, incluindo o status de sucesso e os diversos status de erro que
 * podem ser retornados. Os seguintes membros estão definidos:
 *
 *     QUEUE_OK                : operação realizada com sucesso
 *     QUEUE_ERRO_QUEUE        : queue inválida
 *     QUEUE_ERRO_ALOCACAO     : erro na alocação de memória
 *     QUEUE_ERRO_ARGUMENTO    : argumento inválido
 *     QUEUE_ERRO_POSICAO      : posição inválida
 *     QUEUE_ERRO_CHEIA        : fila cheia
 *     QUEUE_ERRO_VAZIA        : fila vazia
 */

typedef enum
{
    QUEUE_OK,
    QUEUE_ERRO_QUEUE,
    QUEUE_ERRO_ALOCACAO,
    QUEUE_ERRO_ARGUMENTO,
    QUEUE_ERRO_POSICAO,
    QUEUE_ERRO_CHEIA,
    QUEUE_ERRO_VAZIA
} queue_status;

/*** Declarações de Subprogramas ***/

/**
 * Função: CRIAR_QUEUE
 * Uso: queue = criar_queue( );
 * ----------------------------
 * Aloca e retorna uma fila vazia. Se não for possível criar a fila, retorna o
 * valor NULL.
 */

queueTAD
criar_queue (void);

/**
 * Função: REMOVER_QUEUE
 * Uso: status = remover_queue(&queue);
 * ------------------------------------
 * Recebe um PONTEIRO para um queueTAD e faz a liberação de todas as estruturas
 * de memória utilizadas pela fila (remove a fila e todos os seus elementos). Os
 * possíveis retornos são:
 *
 *     a) QUEUE_OK: operação realizada com sucesso (o ponteiro "queue" informado
 *        será direcionado para NULL);
 *     b) QUEUE_ERRO_ARGUMENTO: ponteiro passado como argumento não é válido; e
 *     c) QUEUE_ERRO_QUEUE: queue inválida.
 *
 * A remoção da queue e liberação correta da memória só ocorrem se a função
 * retornar QUEUE_OK. É responsabilidade do cliente passar um ponteiro válido, e
 * que aponte para uma queue válida.
 */

queue_status
remover_queue (queueTAD *queue);

/**
 * Função: ENQUEUE
 * Uso: status = enqueue(queue, elemento);
 * ---------------------------------------
 * Recebe uma "queue" e um "elemento", e enfileira o elemento no final da fila.
 * Os possíveis retornos são:
 *
 *     a) QUEUE_OK: operação realizada com sucesso;
 *     b) QUEUE_ERRO_QUEUE: queue inválida; e
 *     c) QUEUE_ERRO_ARGUMENTO: elemento inválido.
 */

queue_status
enqueue (queueTAD queue, const elementoT elemento);

/**
 * Função: DEQUEUE
 * Uso: status = dequeue(queue, &elemento);
 * ----------------------------------------
 * Recebe uma "queue" e um PONTEIRO para um "elemento". Se a operação for
 * realizada com sucesso, desenfileira o elemento no início da fila e coloca
 * esse elemento no endereço apontado por "elemento".
 * Os possíveis retornos são:
 *
 *     a) QUEUE_OK: operação realizada com sucesso;
 *     b) QUEUE_ERRO_QUEUE: queue inválida;
 *     c) QUEUE_ERRO_ARGUMENTO: ponteiro elemento inválido; e
 *     d) QUEUE_ERRO_VAZIA: queue vazia.
 *
 * O valor armazenado no local apontado por "elemento" só é válido e confiável
 * se a função tiver retornado QUEUE_OK.
 */

queue_status
dequeue (queueTAD queue, elementoT *elemento);

/**
 * Função: VAZIA
 * Uso: if (vazia(queue, &esta_vazia) == QUEUE_OK && esta_vazia == true) . . .
 * ---------------------------------------------------------------------------
 * Recebe uma "queue" e um PONTEIRO para um booleano "esta_vazia", e retorna
 * valores que nos permitem identificar se a fila está vazia ou não (ou, se
 * ocorrer algum erro, permitem identificar esse erro). Os seguintes retornos
 * são possíveis:
 *
 *     a) QUEUE_OK: operação realizada com sucesso; "esta_vazia" contém o valor
 *        booleano indicativo de fila vazia (true) ou não vazia (false);
 *     b) QUEUE_ERRO_ARGUMENTO: ponteiro "esta_vazia" inválido; e
 *     c) QUEUE_ERRO_QUEUE: queue inválida.
 *
 * O valor true ou false armazenado em "esta_vazia" só é válido se o retorno da
 * função tiver sido QUEUE_OK.
 */

queue_status
vazia (const queueTAD queue, bool *esta_vazia);

/**
 * Função: CHEIA
 * Uso: if (cheia(queue, &esta_cheia) == QUEUE_OK && esta_cheia == true) . . .
 * ---------------------------------------------------------------------------
 * Recebe uma "queue" e um PONTEIRO para um booleano "esta_cheia", e retorna
 * valores que nos permitem identificar se a fila está cheia ou não (ou, se
 * ocorrer algum erro, permitem identificar esse erro). Os seguintes retornos
 * são possíveis, nas seguintes situações:
 *
 *     a) QUEUE_OK: operação realizada com sucesso; "esta_cheia" contém o valor
 *        booleano indicativo de fila cheia (true) ou não cheia (false);
 *     b) QUEUE_ERRO_ARGUMENTO: ponteiro "esta_cheia" inválido;
 *     c) QUEUE_ERRO_QUEUE: queue inválida.
 *
 * A implementação definirá se a fila é fixa ou dinâmica e, caso a fila seja
 * dinâmica, esta função sempre retornará false se as operações de aumento de
 * tamanho forem realizadas com sucesso. Se a fila não puder ser aumentada de
 * tamanho por algum problema ou limitação de recursos, a função colocará true
 * em "esta_cheia" e retornará o erro: QUEUE_ERRO_ALOCACAO.
 *
 * O valor true ou false armazenado em "esta_cheia" só é válido se o retorno da
 * função tiver sido QUEUE_OK.
 */

queue_status
cheia (const queueTAD queue, bool *esta_cheia);

/**
 * Função: NUM_ELEMENTOS
 * Uso: status = num_elementos(queue, &nelem);
 * ------------------------------------------
 * Recebe uma "queue" e armazena no local apontado pelo ponteiro "nelem" o
 * tamanho efetivo da fila ou seja, a quantidade atual de elementos armazenados
 * na fila. Os seguintes retornos são possíveis nas seguintes situaçoes:
 *
 *     a) QUEUE_OK: operação realizada com sucesso; "nelem" contém a quantidade
 *        atual de elementos na fila;
 *     b) QUEUE_ERRO_ARGUMENTO: ponteiro "nelem" inválido; e
 *     c) QUEUE_ERRO_QUEUE: queue inválida.
 */

queue_status
num_elementos (const queueTAD queue, size_t *nelem);

/**
 * Função: INFO
 * Uso: status = info(queue, &din, &tamax);
 * ----------------------------------------
 * Esta função não faz parte dos comportamentos normais esperados para uma fila
 * mas é definida nesta interface para que o cliente possa obter diversas
 * informações sobre a fila e sua implementação interna como, por exemplo, se a
 * impementação se dá através de uma fila fixa (o tamanho máximo alocado não
 * se altera) ou de uma fila dinâmica (o tamanho alocado aumenta automaticamente
 * em tempo de execução e, assim, não há um tamanho máximo). Os seguintes
 * retornos são possíveis:
 *
 *     a) QUEUE_OK: operação realizada com sucesso;
 *            - "din" conterá true se a fila for dinâmica, ou false caso não; e
 *            - "tamax" conterá -1 se a fila for dinâmica, ou o tamanho máximo
 *              definido para a fila (de tamanho fixo).
 *     b) QUEUE_ERRO_ARGUMENTO: ponteiro "din" ou "tammax" inválido (nesse caso
 *        o próprio cliente deve verificar a validade dos ponteiros antes de
 *        passá-los para esta função);
 *     c) QUEUE_ERRO_QUEUE: queue inválida.
 *
 * Os valores armazenados em "din" e "tamax" só são válidos e confiáveis se o
 * retorno da função tiver sido QUEUE_OK.
 */

queue_status
info (const queueTAD queue, bool *din, int *tamax);

/**
 * Função: VER_ELEMENTO
 * Uso: status = ver_elemento(queue, posicao, &elemento);
 * ------------------------------------------------------
 * Esta função NÃO ESTÁ PRESENTE em situações normais de uso da fila, mas é
 * definida aqui apenas para ser utilizada em situações de DEBUG, pois não é um
 * comportamento padrão de uma fila. A função retorna o elemento especificado na
 * "posicao" no endereço apontado por "elemento", SEM DESENFILEIRAR o elmento. O
 * início da fila é definido como posição 0 (zero). Os seguintes retornos são
 * possíveis:
 *
 *     a) QUEUE_OK: operação realizada com sucesso; "elemento" contém o elemento
 *        na posição indicada, sem desenfileirar;
 *     b) QUEUE_ERRO_ARGUMENTO: ponteiro "elemento" inválido;
 *     c) QUEUE_ERRO_QUEUE: queue inválida; e
 *     d) QUEUE_ERRO_POSICAO: posição inválida.
 *
 * O cliente deve informar uma posição não negativa válida, ou seja, de 0 até
 * (nelem - 1).
 */

#ifdef debug
queue_status
ver_elemento (const queueTAD queue, const size_t posicao, elementoT *elemento);
#endif

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
priority_enqueue(queueTAD queue, const elementoT elemento, int prioridade);
 
/*** Finaliza Boilerplate da Interface ***/

#endif
