/*Considere que você está implementando o histórico de links visitados em um navegador
utilizando uma pilha. Neste caso, você deve implementar uma pilha dinâmica que armazene o
struct apresentado abaixo. Um recurso importante do navegador permite que o usuário volte
para qualquer site do histórico (elemento no meio da pilha) e, para isso, você deve implementar
o método site* voltar(Pilha *p, int n) que recebe uma pilha de sites, juntamente com um
determinado número n que indica quantos sites devemos voltar. Portanto, o método irá
desempilhar n elementos da pilha e retornar o novo topo.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reg_site{
    char nome[50];
    char link[100];
    reg_site *prox;
} site;
typedef struct reg_site Pilha;


void push(Pilha **stack, site *ele){
    ele->prox = *stack;
    *stack = ele;
}

void imprimir(Pilha *stack){
    while(stack != NULL){
        printf(" ""%s"" link -> %s\n", stack->nome, stack->link);
        stack = stack->prox;
    }
}
Pilha *stack_N (Pilha *stack, char *nome, char *link){
    stack = (Pilha*)malloc(sizeof(Pilha));
    strcpy(stack->nome, nome);
    strcpy(stack->link, link);
    return stack;

}
site* voltar(Pilha *p, int n){
    int i = 0;
    while(p!= NULL && i < n){
        n-=1;
        p = p->prox;
    }
    return p;

}
int main(){

    Pilha *stac = NULL;
    site *el1;
    site *el2;
    site *el3;
    site *el4;
    
    el1 = stack_N(el1, "GOL", "www.GOL.com.br");
    el2 = stack_N(el2, "JAVA", "www.JAVA.com.br");
    el3 = stack_N(el3, "PYTHON", "www.PYTHON.com.br");
    el4 = stack_N(el4, "CCC", "www.CCC.com.br");

    push(&stac, el1);
    push(&stac, el2);
    push(&stac, el3);
    push(&stac, el4);
    printf("     ------Sites------\n");
    imprimir(stac);
    printf("     -----------------\n");

    stac = voltar(stac, 1);
    printf("     ------Voltando 1------\n");
    imprimir(stac);
    printf("     -----------------\n");

    stac = voltar(stac, 2);
    printf("     ------volando mais 2------\n");
    imprimir(stac);
    printf("     -----------------\n");



    return 0;
}

