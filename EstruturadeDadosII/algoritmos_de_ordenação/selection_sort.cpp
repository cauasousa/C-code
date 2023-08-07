#include <stdio.h>

void selection_sort(int *vetor, int quant){

    for(int i = 0; i < quant ; i++){
        int menor = i;
        for(int j = i + 1; j < quant; j++){

            if(vetor[menor] > vetor[j]){

                menor = j;

            }
            
        }
        if(menor != i ){
            int aux = vetor[menor];
            vetor[menor] = vetor[i];
            vetor[i] = aux;
        }
        
    }
}


int main(){
    int vetor[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    selection_sort(vetor, 10);
    printf("\n\nOrdenadação");
    for(int i = 0; i < 10; i++){
        printf(" %d", vetor[i]);
    }

    return 0;
}