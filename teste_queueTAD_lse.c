#include <stdio.h>
#include <stdlib.h>
#include "queueTAD.h"

int main()
{
    queueTAD queue = criar_queue();

    elementoT x = {10, 3};
    elementoT y = {20, 1};
    elementoT z = {30, 2};

    priority_enqueue(queue, x, x.prioridade);
    priority_enqueue(queue, y, y.prioridade);
    priority_enqueue(queue, z, z.prioridade);

    elementoT elemento;
    bool esta_vazia;

   do {
        // Verifica se a fila está vazia
        if (vazia(queue, &esta_vazia) != QUEUE_OK) {
            printf("Erro ao verificar se a fila está vazia.\n");
            break;
        }

        // Continua apenas se a fila não está vazia
        if (!esta_vazia) {
            if (dequeue(queue, &elemento) == QUEUE_OK) {
                printf("Valor: %d, Prioridade: %d\n", elemento.valor, elemento.prioridade);
            } else {
                printf("Erro ao remover elemento da fila.\n");
            }
        }
    } while (!esta_vazia);

    remover_queue(&queue);

    return 0;
}
