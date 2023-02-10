#include <stdio.h>
#include <stdlib.h>

typedef struct fala
{
    int num;
    fala *prox;
} fila;

fila *ins()
{
    fila *nova = (fila *)malloc(sizeof(fila));
    printf("\nNm: ");
    scanf("%d", &nova->num);
    nova->prox = NULL;
    return nova;
}

void enfileirar(fila **firts, fila **last, fila *novo)
{
    if (*last == NULL)
    {
        *last = novo;
        *firts = novo;
        return;
    }
    (*last)->prox = novo;
    *last = novo;
    return;
}

void imprimir(fila *aux)
{
    printf("\n\tFila\n");
    while (aux != NULL)
    {
        printf("%d -", aux->num);
        aux = aux->prox;
    }
    printf(" Ultimo ");
}

fila *ter(fila **Firts_1, fila **Last_1, fila **firts_2, fila **last_2, fila **last_33)
{
    fila *nova = NULL;
    fila *aux1 = *Firts_1, *aux_2 = *firts_2, *aux_3 = NULL;

    while (aux1 != NULL)
    {
        aux_3 = aux1;
        aux1 = aux1->prox;
        aux_3->prox = NULL;

        enfileirar(&nova, last_33, aux_3);
        //printf("Opa - ");
    }
    if (*Last_1 != NULL)
    {
        *Firts_1 = NULL;
        *Last_1 = NULL;
    }
    while (aux_2 != NULL)
    {
        aux_3 = aux_2;
        aux_2 = aux_2->prox;
        aux_3->prox = NULL;

        enfileirar(&nova, last_33, aux_3);
        //printf("Nada - ");

    }
    if (*last_2 != NULL)
    {
        *firts_2 = NULL;
        *last_2 = NULL;
    }
    return nova;
}

int main()
{
    fila *firts = NULL, *last = NULL, *aux = NULL;
    fila *firts_2 = NULL, *last_2 = NULL;

    aux = ins();
    enfileirar(&firts, &last, aux);
    aux = ins();
    enfileirar(&firts, &last, aux);
    aux = ins();
    enfileirar(&firts, &last, aux);

    aux = ins();
    enfileirar(&firts_2, &last_2, aux);
    aux = ins();
    enfileirar(&firts_2, &last_2, aux);
    aux = ins();
    enfileirar(&firts_2, &last_2, aux);

    printf("\nFila 1\t");
    imprimir(firts);
    printf("\nFila 2\t");
    imprimir(firts_2);

    fila *terc = NULL;
    fila *ter_last = NULL;
    terc = ter(&firts, &last, &firts_2, &last_2, &ter_last);
    printf("\nFila 3\t");
    imprimir(terc);

    return 0;
}