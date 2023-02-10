/*1. Considere que você está implementando um sistema de atendimento de pacientes para um
hospital. Neste caso, você deve implementar uma fila dinâmica que armazene o struct
apresentado abaixo. Observou-se que, durante a espera, os pacientes sempre perguntam
quando quantas pessoas estão na sua frente. Desta forma, você deve implementar o método
int pessoasNaFrente(Fila *f, char* nome), que recebe a fila de pacientes juntamente com o
nome de um determinado paciente e retorna a quantidade de pacientes na frente dele.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fala
{
    char nome[50];
    char plano_saude[100];
    int num;
    fala *prox;
} fila;

fila *ins()
{
    fila *nova = (fila *)malloc(sizeof(fila));
    printf("\nNm: ");
    scanf("%d", &nova->num);
    printf("\nNome: ");
    scanf(" %[^\n]s", nova->nome);
    nova->prox = NULL;
    return nova;
}

void enfileirar(fila **firts, fila **last, fila *e){
    if(*firts == NULL){
        *firts = e;
        *last = e;
        return ;
    }
    (*last)->prox = e;
    *last = (*last)->prox;
}

int pessoasNaFrente(fila *f, char* nome){
    int i = 0, j = 0;
    while(f!=NULL){
        if(strcmp(f->nome, nome)==0){
            j++;
            break;
        }
        i++;
        f = f->prox;
    }
    if(j>0){return i;}else{return -1;}
    /*if(f != NULL){
        while(f!=NULL){
            i++;
            f = f->prox;
        }
        return i;        
    }*/
    return -1;
}

int main(){

    fila *firts = NULL, *last = NULL, *aux = NULL;

    aux = ins();
    enfileirar(&firts, &last, aux);
    aux = ins();
    enfileirar(&firts, &last, aux);
    aux = ins();
    enfileirar(&firts, &last, aux);

    char nome[] = "caua";
    int i = pessoasNaFrente(firts, nome);
    printf("\n %d", i);
    char nome1[] = "ana";
    i = pessoasNaFrente(firts, nome1);
    printf("\n %d", i);
    char nome2[] = "fdp";
    i = pessoasNaFrente(firts, nome2);
    printf("\n %d", i);


}