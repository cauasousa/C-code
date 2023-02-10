/*3. Escreva um programa que implemente uma fila circular utilizando um vetor como estrutura de
armazenamento dos dados. O programa deve ser capaz de inserir, remover e informar o
tamanho da fila em um dado momento.*/

#include <stdio.h>
#include <stdlib.h>
#define TAM 5

typedef struct fila
{
    int num[TAM];
    int firts = -1;
    int last = -1;
} Fila;
// 0 - 0 - 1 - 2
// 3 - 1= 1

void enquete(Fila *f, int e)
{
    if (f->last - f->firts == TAM - 1)
    {
        printf("Fila Cheia!");
        return;
    }
    if (f->last - f->firts == -1)
    {
        printf("Fila Cheia!");
        return;
    }
    if (f->firts == -1)
    {
        f->firts += 1;
        f->last += 1;
        f->num[f->firts] = e;
        return;
    }
    f->last += 1;
    if (f->last >= TAM)
    {
        // printf("\t\t\t>>%d",f->last);
        f->last = 0;
    }

    f->num[f->last] = e;
}

void desf(Fila *f, int n)
{
    if (f->firts == -1)
    {
        printf("Vazia");
        return;
    }
    if (f->firts == f->last)
    {
        // printf("Um elemnto Elim");
        f->firts = -1;
        f->last = -1;
        return;
    }
    if (f->firts == TAM - 1)
    {
        // printf("No final");
        f->firts = 0;
        return;
    }

    f->firts += 1;
    // printf("Normal %d\n", f->firts);
}
void imprimir(Fila *e)
{
    printf("---Fila -->>");
    if (e->firts == 0)
    {
        for (int i = e->firts; i <= e->last; i++)
        {
            printf(" - %d ", e->num[i]);
        }
        return;
    }
    else if (e->last < TAM && e->last >= e->firts)
    {
        for (int i = e->firts; i <= e->last; i++)
        {
            printf(" - %d ", e->num[i]);
        }
        printf("'-'");
        return;
    }

    int j = 0;
    int i = e->firts;
    // while (i - e->firts != -1)
    while (i != e->last + 1)
    {

        printf(" ->%d", e->num[i]);
        j++;
        if (i == TAM - 1)
        {
            i = 0;
        }
        else
        {
            i = i + 1;
        }
        // system("pause");
    }
    // printf("FIM");

    printf(" FIM");
}

int main()
{
    Fila opa;
    // printf("\nPos -> %d\n", opa.last);
    for (int i = 0; i < 2; i++)
    {
        enquete(&opa, i);
    }
    // printf("\nPos -> %d", opa.last);
    // printf("\nAdicinou 2\t");
    // imprimir(&opa);

    for (int i = 2; i < 5; i++)
    {
        enquete(&opa, i);
    }
    // printf("\n\nPos -> %d", opa.last);
    // printf("\nAdicinou +2\t");
    imprimir(&opa);
    /*   for(int i = 5; i<10; i++){
           enquete(&opa, i);
       }
       printf("\n\nPos -> %d", opa.last);
       printf("\nAdicinou +2\t");
       imprimir(&opa);*/

    printf("\n--- -1 ---\n");
    desf(&opa, 1);
    imprimir(&opa);

    printf("\n--- -1 ---\n");
    desf(&opa, 1);
    imprimir(&opa);

    printf("\n--- -1 ---*\n");
    for (int i = 0; i < 2; i++)
    {
        desf(&opa, 0);
    }
    imprimir(&opa);
    printf("\nPos do Primeiro: %d , Pos do Ultimo: %d", opa.firts, opa.last);
    printf("\nAD 2\n");
    for (int i = 20; i < 22; i++)
    {
        enquete(&opa, i);
    }
    // system("pause");

    imprimir(&opa);
    printf("\nPos do Primeiro: %d , Pos do Ultimo: %d", opa.firts, opa.last);
    printf("\nOPAA   ");
    desf(&opa, 0);
    imprimir(&opa);
    printf("\nPos do Primeiro: %d , Pos do Ultimo: %d", opa.firts, opa.last);

    return 0;
}