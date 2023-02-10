#include <stdio.h>
#include <stdlib.h>


int main(void) {

    float *vetor, soma = 0;
    int n; 
    printf("DIgite a qunt: ");
    scanf("%d", &n);

    vetor = (float *)(malloc(5 * sizeof(int)));

    for (int i = 0; i < n; i++) {
      printf("Pos. %d: ", (i + 1));
      scanf("%f", &vetor[i]);
      soma = soma + vetor[i];
    }

    float media = (soma / n);
    printf("%.2f \n", media);

    for(int i = 0; i<n; i++){
      printf("%f", vetor[i]);
    }
    
    free(vetor);
    printf("%.2f", media);
    printf("Hello World\n");
    return 0;
}