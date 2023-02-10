//Faca um programa que aloque memoria para um vetor de inteiros  e mostra o maior é menor numero dentro do vetor
#include <stdio.h>
#include <stdlib.h>

int main(){

    int n;
    int *vetor = NULL; 
    
    printf("Quantidade de Alocação? ");
    scanf("%d", &n);

    vetor = (int*)malloc( sizeof(int) * n);

    for (int i = 0; i < n; i++){

        printf("\nDigite Valor da Posição %d->> ", i+1);
        scanf("%d", &vetor[i]);

    }
    printf("Vetor: ");
    for (int i = 0; i < n; i++){

        printf(" | %d ", i + 1, vetor[i] );

    }

    return 0;

}