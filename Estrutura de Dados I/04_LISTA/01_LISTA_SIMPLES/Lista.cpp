#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct dados{
    char nome[50];
    int nota;

    dados *prox;
} chama;

void inserir_comeco ( chama **cabeca){
    chama *novo = (chama*)malloc(sizeof(chama));

    printf("\n\t\tNome: ");
    scanf(" %50[^\n]s", novo->nome);
    printf("\n\t\tNota: ");
    scanf("%d", &novo->nota);

    novo->prox = *cabeca;
    *cabeca = novo;
}

void imprimir(chama **cabeca){
    chama *aux;
    aux = *cabeca;

    while(aux != NULL){

        printf("\n\t\tLista-->");
        printf("\t\tNome: %s", aux->nome);
        printf("\t\tNota: %d", aux->nota);      

        aux = aux->prox;
    }
    printf("\n\t\t\t-->NULL;");

};

chama *inserir(){
    chama *novo = (chama*)malloc(sizeof(chama));

    printf("\n\t\tNome: ");
    scanf(" %50[^\n]s", novo->nome);
    printf("\n\t\tNota: ");
    scanf("%d", &novo->nota);

    return novo;
}

void inserir_meio(chama **cabeca, char ant[50]){
    chama *aux;
    aux = *cabeca;

    chama *Novo;
    Novo = inserir();

    if (*cabeca == NULL){
        Novo->prox = NULL;
        *cabeca = Novo;
    }

    else{

        while(strcmp(aux->nome, ant) != 0 && aux->prox != NULL ){
            aux = aux->prox;
        }

        Novo-> prox = aux->prox;
        aux->prox = Novo;

    }


}

void inserir_final(chama **cabeca){
    chama *Novo;
    Novo = inserir();
    chama *aux;
    aux = *cabeca;

    if(*cabeca == NULL){
        Novo->prox = NULL;
        *cabeca = Novo;
    }
    else {
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        

        aux->prox = Novo;
        Novo->prox = NULL;
    }

}

int main(){
    chama *head = NULL;
    printf("-------------Comeco-------------");

    inserir_comeco(&head);
    inserir_comeco(&head);
    printf("-------------MEIO--------------");

    imprimir(&head);
    inserir_meio(&head, "caua");
    imprimir(&head);
    printf("-------------FINAL--------------");
    inserir_final(&head);
    imprimir(&head);




    return 0; 
}