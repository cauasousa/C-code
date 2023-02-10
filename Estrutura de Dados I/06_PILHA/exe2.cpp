#include <stdio.h>
#include <stdlib.h>

typedef struct stacks{
    int num;
    stacks *prox;
}Pilha;

Pilha *ins(){
    Pilha *nova = (Pilha*)malloc(sizeof(Pilha));
    printf("\nNm: ");
    scanf("%d", &nova->num);
    nova->prox = NULL;
    return nova;
}

void ins(Pilha **p, Pilha *novo){
    novo->prox = *p;
    *p = novo;
}

void imprimir(Pilha *aux){
    printf("\n\tPilha\n");
    while(aux != NULL){
        printf("%d\n", aux->num);
        aux = aux->prox;
    }
}

Pilha *nova_pilha_invert(Pilha **pp){
    Pilha *novo = NULL, *pn = NULL, *p = *pp;
    while(p != NULL){
        pn = p;
        p = p->prox;
        ins(&novo, pn);
    }
    *pp = NULL;
    return novo;
}

int main(){
    Pilha *stack = NULL;
    Pilha *stack2 = NULL;
    Pilha *aux = ins();
    ins(&stack, aux);
    aux = ins();
    ins(&stack, aux);
    aux = ins();
    ins(&stack, aux);
    imprimir(stack);
    printf("\n-----------\n");
    stack2 = nova_pilha_invert(&stack);
    imprimir(stack);
    printf("\n------Nova-----\n");

    imprimir(stack2);



    return 0;
}