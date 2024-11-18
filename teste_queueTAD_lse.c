#include <stdio.h>
#include <stdlib.h>
#include "queueTAD.h"

int main()
{
    queueTAD queue = criar_queue();

    int x[] = {10, 3};
    int y[] = {20, 1};
    int z[] = {30, 2};

    priority_enqueue(queue, x, x[1]);
    priority_enqueue(queue, y, y[1]);
    priority_enqueue(queue, z, z[1]);

    elementoT elemento;
    while (vazia(queue, NULL) != QUEUE_OK)
    {
        dequeue(queue, &elemento);
        printf("Valor: %d, Prioridade: %d\n", ((int *)elemento)[0], ((int *)elemento)[1]);
    }

    remover_queue(&queue);

    return 0;
}