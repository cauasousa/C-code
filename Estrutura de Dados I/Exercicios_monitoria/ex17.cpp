//17.Foi realizada uma pesquisa de algumas características físicas de 50
//habitantes de uma certa região. De cada habitante foram coletados os
//seguintes dados: sexo, cor dos olhos (azuis, verdes ou castanhos), cor
//dos cabelos (louros, pretos ou castanhos) e idade. Faça um procedimento
//que leia esses dados em um vetor de registro. O vetor de registro deve
//ser enviado por referência.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int num = 2;

typedef struct registro{

    char sexo[20], cor_olhos[10], cor_cabelo[15];
    int idade;
    
}chama;

void inserir( chama *head){

    for(int i = 0; i<num; i++){
        //
        while(strcmp(head[i].sexo, "masculino") != 0 && strcmp(head[i].sexo, "femenino") != 0){
            printf("\n\t\tDigite 'femenino' ou 'masculino");
            printf("\n\t\tDiga o sexo ");
            scanf(" %20[^\n]s", head[i].sexo);    

            if(strcmp(head[i].sexo, "masculino") && strcmp(head[i].sexo, "feminino") != 0){
                system("cls");
                printf("\n\t\tSexo inserido incorreto");

            }
        }
        //cor dos olhos (azuis, verdes ou castanhos)
            while(strcmp(head[i].cor_olhos, "azul") != 0 && strcmp(head[i].cor_olhos, "verde") != 0 && strcmp(head[i].cor_olhos, "castanhos") != 0){
                    printf("\n\t\tCor dos olhos: 'azul' ou 'verde' ou 'castanhos' ");
                    printf("\n\t\tDiga o COr dos olhos ");
                    scanf(" %20[^\n]s", head[i].cor_olhos);
                    
                        if(strcmp(head[i].cor_olhos, "azuis") && strcmp(head[i].cor_olhos, "verdes") != 0 && strcmp(head[i].cor_olhos, "castanhos") != 0){
                        system("cls");
                        printf("\n\t\t inserido incorreto");

                    }  
            }
            //cor
            //dos cabelos (louros, pretos ou castanhos)
            while(strcmp(head[i].cor_cabelo, "louro") != 0 && strcmp(head[i].cor_cabelo, "preto") != 0 && strcmp(head[i].cor_cabelo, "castanhos") != 0){
                    printf("\n\t\tCor dos olhos: 'louro' ou 'preto' ou 'castanhos' ");
                    printf("\n\t\tDiga o cor do cabelo ");
                    scanf(" %20[^\n]s", head[i].cor_cabelo);  
                    
                        if(strcmp(head[i].cor_cabelo, "louros") && strcmp(head[i].cor_cabelo, "pretos") != 0 && strcmp(head[i].cor_cabelo, "castanhos") != 0){
                        system("cls");
                        printf("\n\t\t inserido incorreto");

                    }  
            }   


        printf("\n\t\tDiga a Idade ");
        scanf("%d", &head[i].idade); 

        printf("------");
    }

}

void imprimir(chama *head){
    for(int i = 0; i<num; i++){
        printf("---*******---");

        printf("\n\t\tsexo %s", head[i].sexo);
        printf("\n\t\tCor dos olhos %s", head[i].cor_olhos);
        printf("\n\t\tCor do cabelo %s", head[i].cor_cabelo);
        printf("\n\t\tIdade %d", head[i].idade);  
        //printf("---*****---");

        }
}

int main(){
    chama *cabeca = (chama*)malloc(sizeof(chama)*num);

    inserir(cabeca);
    imprimir(cabeca);

    
    return 0;
}