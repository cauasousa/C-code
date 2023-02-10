#include <stdio.h>
#include <stdlib.h>
int N = 0;
typedef struct reg_site
{
    char nome[50];
    char link[100];
    struct reg_site *prox;
} site;

typedef struct pil
{
    site *pilha;
} Pilha;

site *ins()
{
    site *nova = (site*)malloc(sizeof(site));
    printf("\n\t\tDigite o nome: ");
    scanf(" %50[^\n]s", nova->nome);
    printf("\n\t\tDigite o site: ");
    scanf(" %100[^\n]s", nova->link);
    nova->prox = NULL;
    return nova;
}
void push(Pilha *ele, site *nov)
{
    nov->prox = ele->pilha;
    ele->pilha = nov;
    //printf(" %s // %s \n ", ele->pilha->nome, ele->pilha->link);

    N++;
    printf("Salvou\n");

}

site *voltar(Pilha *P, int n)
{
    int i = 0;
    //printf("\n\t\t\t%d", n);
    site *p = P->pilha;
    if (n <= N)
    {
        while (p != NULL && n>i)
        {
            site *lixo = p;
            p = p->prox;
            i++;
            N--;
            lixo->prox = NULL;

        }
        //printf("F\n");

        return p;
    }
    else
    {
        printf("\nImpossível voltar esse tanto");
        return P->pilha;
    }
}

void imprimir(Pilha p)
{
    site *aux = p.pilha;
    while (aux != NULL)
    {
        printf("\n%s // %s", aux->nome, aux->link);
        aux = aux->prox;
    }
    printf(" FIM_NULL \n ");
}

int main()
{
    
    Pilha pilh;
    pilh.pilha = NULL;
    
    site *n1 = ins();
    push(&pilh, n1);
    site *n2 = ins();
    push(&pilh, n2);
    site *n3 = ins();
    push(&pilh, n3);
    imprimir(pilh);

    printf("\n----0-------");
    pilh.pilha = voltar(&pilh, 0);
    imprimir(pilh);
    printf("\n------1-----");
    pilh.pilha = voltar(&pilh, 1);
    imprimir(pilh);
    printf("\n-----2------\n");
    site *n5 = ins();
    push(&pilh, n5);
    pilh.pilha = voltar(&pilh, 2);
    imprimir(pilh);
    printf("\n-----NADA------\n");
    pilh.pilha = voltar(&pilh, 3);
    imprimir(pilh);
    pilh.pilha = voltar(&pilh, 4);
    imprimir(pilh);
    return 0;
}