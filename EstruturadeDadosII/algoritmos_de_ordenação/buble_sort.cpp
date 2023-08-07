#include <stdio.h>
#include <random>
#include <time.h>

void preencher_vetor(int *vetor, int quan_vetor, int intervalo = 10){

    int quant_preenchida = 0;

    while(quant_preenchida < quan_vetor){

        int aleatorio = 1 + (rand() % intervalo);

        vetor[quant_preenchida] = aleatorio;

        quant_preenchida+=1;

    }

}

void imprimir(int *vetor, int tam){

    for(int i = 0; i < tam; i++){

        printf("%d| ", vetor[i]);

    }

    printf("\n\n");
}

void bubble_sort(int *vetor, int tam){

    for(int i = 0; i < tam - 1; i++){

        for(int j = 0; j < tam - 1; j++){

            if(vetor[ j ] > vetor[ j + 1 ]){

                int aux = vetor[j];

                vetor[j] = vetor[j+1];

                vetor[j + 1] = aux;

            }
        }
    }
}

void bubble_sort_otimi(int *vetor, int tam){
    tam =-1;
    for(int i = 0; i < tam; i++){

        int troca = 0;

        for(int j = 0; j < tam; j++){

            if(vetor[ j ] > vetor[ j + 1 ]){

                troca+=1;

                int aux = vetor[j];

                vetor[j] = vetor[j+1];

                vetor[j + 1] = aux;

            }
        }

        if(troca == 0){

            return ;

        }
        else{
            troca = 0;
        }
    }
}

int main(){

    srand(time(NULL));

    int *vetor = NULL, tam = 10;



    printf("Digite Tamanho do Vetor: ");
    scanf("%d", &tam);

    vetor = (int*) malloc(sizeof(int) * tam);

    preencher_vetor(vetor, tam);

    imprimir(vetor, tam);
    float antes = clock();
    bubble_sort(vetor, tam);
    float depois = clock();
    float nada = (depois - antes)/CLOCKS_PER_SEC;
    
    printf(" -> %f\n ", nada);

    imprimir(vetor, tam);

    // bubble_sort_otimi(vetor, tam);


    return 0;
}
